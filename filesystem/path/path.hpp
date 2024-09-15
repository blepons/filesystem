#ifndef FILESYSTEM_PATH_HPP_
#define FILESYSTEM_PATH_HPP_

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace Filesystem {

/*!
 * \brief Represents a filesystem path.
 */
class Path {
public:
    /*!
     * \brief Contructs a Path object from given string_view.
     * \param path Path represented as std::string_view.
     * \throws std::invalid_argument If path is empty.
     * \throws std::invalid_argument If one of the filenames is empty.
     */
    explicit Path(std::string_view path);

    /*!
     * \brief Checks if the path is absolute.
     * \return True if the path is absolute, false otherwise.
     */
    [[nodiscard]] bool is_absolute() const noexcept { return absolute_; };

    /*!
     * \brief Returns the size of the path.
     * \return The size of the path, including parent directory calls.
     */
    [[nodiscard]] std::size_t size() const noexcept {
        return path_.size() + parent_dir_calls_;
    };

    /*!
     * \brief Checks if the path is empty.
     * \return True if the path is empty, false otherwise.
     */
    [[nodiscard]] bool empty() const noexcept { return size() == 0; };

    /*!
     * \brief Joins the current path with another path.
     * \param path The path to join with.
     * \return A reference to the current Path object.
     */
    Path& join_with(const Path& path);

    /*!
     * \brief Converts the current path to an absolute path.
     *
     * Converts the current path to an absolute path
     * with respect to the current directory.
     *
     * \return A reference to the current Path object.
     */
    Path& absolutize();

    /*!
     * \brief Converts the current path to a relative path.
     *
     * Relativizes the current path with respect to a base path.
     *
     * \param base_path The base path to relativize against.
     * \return A reference to the current Path object.
     * \throws std::invalid_argument If this or base_path are absolute.
     */
    Path& relativize(const Path& base_path);

    /*!
     * \brief Converts the current path to a relative path.
     *
     * Relativizes the current path with respect to
     * the current work directory.
     *
     * \return A reference to the current Path object.
     */
    Path& relativize();

    /*!
     * \brief Return the string representation of the path.
     * \return Path represented as std::string.
     */
    [[nodiscard]] std::string string() const;

private:
    std::vector<std::string> path_; ///< The components of the path.
    std::size_t parent_dir_calls_ = 0; ///< Number of parent directory calls.
    bool absolute_ = false; ///< Indicates if the path is absolute.

    /*!
     * \brief Processes a parent directory call.
     */
    void parent_dir();

    /*!
     * \brief Processes a specified number of parent directory calls.
     * \param n The number of parent directory calls.
     */
    void parent_dir(std::size_t n);

    /*!
     * \brief Processes a directory component of the path.
     * \param dir The directory component represented as std::string_view.
     */
    void process_dir(const std::string_view dir);
};

}  // namespace Filesystem

#endif  // !FILESYSTEM_PATH_HPP_
