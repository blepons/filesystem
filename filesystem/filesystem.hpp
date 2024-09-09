#ifndef OOP_1_FILESYSTEM_HPP_
#define OOP_1_FILESYSTEM_HPP_

#include <string>
#include <string_view>

namespace Filesystem {

/*!
 * \brief Joins a base path with an appended path.
 *
 * \param base The base path.
 * \param appended The path to append.
 * \return A string representing joined path.
 * \throws std::invalid_argument If appended is absolute.
 * \throws std::invalid_argument If base or appended are empty.
 */
std::string join(std::string_view base, std::string_view appended);

/*!
 * \brief Converts a given path to an absolute path.
 *
 * Converts a given path to an absolute path with respect to
 * the current directory.
 * If paht is already absolute, does nothing except formatting.
 *
 * \param path The path to convert.
 * \return A string representing absolute path.
 * \throws std::invalid_argument If path is empty.
 */
std::string absolute(std::string_view path);

/*!
 * \brief Relativizes a target path with respect to a base path.
 *
 * Converts a target path to a relative path with respect to
 * the base path.
 *
 * \param base The base path.
 * \param path The path to relativize.
 * \return A string representing relativized path.
 * \throws std::invalid_argument If base or path are absolute.
 * \throws std::invalid_argument If base or path are empty.
 */
std::string relativize(std::string_view base, std::string_view path);

/*!
 * \brief Converts a given path to a relative path.
 *
 * Converts a given path to a relative path with respect to
 * the current working directory.
 * If path is already relative, does nothing except formatting.
 *
 * \param path The path to relativize.
 * \return A string representing relativized path.
 * \throws std::invalid_argument If path is empty.
 */
std::string relative(std::string_view path);

}  // namespace Filesystem

#endif  // !OOP_1_FILESYSTEM_HPP_
