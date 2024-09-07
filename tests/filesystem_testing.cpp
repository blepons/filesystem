#include <catch2/internal/catch_section.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "filesystem.hpp"

namespace Fs = Filesystem;

TEST_CASE("Joining") {
    REQUIRE(Fs::join("/tmp", "abc") == "/tmp/abc/");
    REQUIRE(Fs::join("relative", "path") == "relative/path/");
    REQUIRE(Fs::join("filesystem/path", "..") == "filesystem/");
    REQUIRE(Fs::join("/sys/kernel/", "../../..") == "/");
    REQUIRE(Fs::join("some/random/path", ".") == "some/random/path/");

    REQUIRE_THROWS(Fs::join("path/to/dir", "/absolute/path/"));
    REQUIRE_THROWS(Fs::join("", "./src"));
    REQUIRE_THROWS(Fs::join("/usr/local", ""));
}

TEST_CASE("Absolutizing") {
    REQUIRE(Fs::absolute("/home/puffy") == "/home/puffy/");
    REQUIRE(Fs::absolute("/") == "/");
}

TEST_CASE("Relativizing") {
        REQUIRE(Fs::relativize("/home/guest/oop/1", "/home/guest/") == "../../");
        REQUIRE(Fs::relativize("/home/guest/", "/home/guest/oop/1") == "oop/1/");
        REQUIRE(Fs::relativize("/home/guest/py", "/home/guest/oop/1") == "../oop/1/");
        REQUIRE(Fs::relativize("/home/guest/oop/1", "/home/guest/py") == "../../py/");
        SECTION("Same paths") {
            const char* path = "/home/guest/";
            REQUIRE(Fs::relativize(path, path) == "./");
        }
        SECTION("Non-absolute args") {
            REQUIRE_THROWS(Fs::relativize("./relative", "/"));
            REQUIRE_THROWS(Fs::relativize("/", "./"));
        }
        REQUIRE(Fs::relative("relative/path") == "relative/path/");

}
