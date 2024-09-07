#include "filesystem.hpp"
#include "path/path.hpp"
#include <stdexcept>
#include <string>
#include <string_view>

namespace Filesystem {

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

std::string relativize(std::string_view base, std::string_view path) {
    return Path{path}.relativize(Path{base}).string();
}

std::string relative(std::string_view path) {
    return Path{path}.relativize().string();
}

}  // namespace Filesystem
