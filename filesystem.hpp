#ifndef OOP_1_FILESYSTEM_HPP_
#define OOP_1_FILESYSTEM_HPP_

#include <string>
#include <string_view>

namespace Filesystem {

std::string join(std::string_view base, std::string_view appended);

} // namespace Filesystem

#endif // !OOP_1_FILESYSTEM_HPP_
