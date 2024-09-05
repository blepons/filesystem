#include "filesystem.hpp"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <iterator>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace Filesystem {

namespace {

#if defined(_WIN32)
constexpr char separator = '\\';
constexpr char root_dir = '\\';
#elif defined(__APPLE__) || defined(__unix__)
constexpr char separator = '/';
constexpr char root_dir = '/';
#endif

namespace ranges = std::ranges;

class Path {
public:
    explicit Path(std::string_view path);

    bool is_absolute() const { return absolute_; };

    Path &join_with(const Path &path);
    Path &absolutize();
    Path &relativize(const Path &base_path);
    Path &relativize();

    std::string string() const;

private:
    std::vector<std::string> path_;
    std::size_t parent_dir_calls_ = 0;
    bool absolute_ = false;

    void parent_dir();
    void parent_dir(std::size_t n);
    void process_dir(std::string_view dir);
};

void Path::parent_dir() {
    if (path_.empty()) {
        ++parent_dir_calls_;
    } else {
        path_.pop_back();
    }
}

void Path::parent_dir(std::size_t n) {
    while (!path_.empty() && n > 0) {
        path_.pop_back();
        --n;
    }
    parent_dir_calls_ += n;
}

void Path::process_dir(std::string_view dir) {
    if (dir == "..") {
        parent_dir();
    } else if (dir != ".") {
        path_.emplace_back(dir);
    }
}

Path::Path(std::string_view path) {
    if (path.empty()) {
        throw std::invalid_argument("path must be non-empty");
    }
    if (path.starts_with(root_dir)) {
        absolute_ = true;
        path = path.substr(1);
    }
    if (path.ends_with(separator)) {
        path = path.substr(0, path.length() - 1);
    }
    auto split =
        path | std::views::split(separator) |
        std::views::transform([](auto rng) { return std::string_view(rng); });
    ranges::for_each(split, [this](const auto dir) { process_dir(dir); });
    if (is_absolute()) {
        parent_dir_calls_ = 0;
    }
}

std::string Path::string() const {
    std::ostringstream stream;
    if (is_absolute()) {
        stream << root_dir;
    } else if (path_.empty()) {
        stream << "." << separator;
    } else {
        ranges::for_each(
            std::views::iota(0U, parent_dir_calls_),
            [&stream](auto) { stream << ".." << separator; });
    }
    auto print = [&stream](const auto &dir) { stream << dir << separator; };
    ranges::for_each(path_, print);
    return stream.str();
}

Path &Path::join_with(const Path &path) {
    parent_dir(path.parent_dir_calls_);
    ranges::for_each(path_, [this](const auto &dir) { process_dir(dir); });
    return *this;
}

Path &Path::absolutize() {
    if (is_absolute()) {
        return *this;
    }
    Path cwd{std::filesystem::current_path().string()};
    cwd.join_with(*this);
    std::swap(*this, cwd);
    return *this;
}

Path &Path::relativize(const Path &base) {
    if (!is_absolute()) {
        throw std::invalid_argument("path must be absolute");
    }
    if (!base.is_absolute()) {
        throw std::invalid_argument("base must be absolute");
    }
    const auto ends = ranges::mismatch(path_, base.path_);
    decltype(path_) new_path(std::from_range,
                             ranges::subrange(ends.in1, ranges::end(path_)));
    parent_dir_calls_ = ranges::distance(ends.in2, ranges::end(base.path_));
    absolute_ = false;
    std::swap(path_, new_path);
    return *this;
}

Path &Path::relativize() {
    if (!is_absolute()) {
        return *this;
    }
    const Path cwd{std::filesystem::current_path().string()};
    return relativize(cwd);
}

} // namespace

std::string join(std::string_view base, std::string_view appended) {
    Path base_p{base};
    const Path appended_p{appended};
    if (appended_p.is_absolute()) {
        throw std::invalid_argument("appended path must be relative");
    }
    return base_p.join_with(appended_p).string();
}

std::string absolute(std::string_view path) {
    return Path{path}.absolutize().string();
}

std::string relativize(std::string_view path, std::string_view base) {
    return Path{path}.relativize(Path{base}).string();
}

std::string relative(std::string_view path) {
    return Path{path}.relativize().string();
}

} // namespace Filesystem
