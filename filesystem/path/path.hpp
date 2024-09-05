#ifndef OOP_1_FILESYSTEM_PATH_HPP_
#define OOP_1_FILESYSTEM_PATH_HPP_

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace Filesystem {

class Path {
public:
    explicit Path(std::string_view path);

    [[nodiscard]] bool is_absolute() const noexcept { return absolute_; };
    Path& join_with(const Path& path);
    Path& absolutize();
    Path& relativize(const Path& base_path);
    Path& relativize();

    [[nodiscard]] std::string string() const;

private:
    std::vector<std::string> path_;
    std::size_t parent_dir_calls_ = 0;
    bool absolute_ = false;

    void parent_dir();
    void parent_dir(std::size_t n);
    void process_dir(const std::string_view dir);
};

}  // namespace Filesystem

#endif  // !OOP_1_FILESYSTEM_PATH_HPP_
