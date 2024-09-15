#include <catch2/internal/catch_section.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "path.hpp"

using namespace Filesystem;

TEST_CASE("Path constructor") {
    SECTION("Absolute") {
        SECTION("'/'") {
            Path root{"/"};
            REQUIRE(root.size() == 0);
            REQUIRE(root.is_absolute() == true);
        }
        SECTION("'/../'") {
            Path root_parent{"/../"};
            REQUIRE(root_parent.size() == 0);
            REQUIRE(root_parent.is_absolute() == true);
        }
        SECTION("'/' at the end doesn't matter") {
            Path with_slash{"/home/puffy/oop/"};
            REQUIRE(with_slash.size() == 3);
            REQUIRE(with_slash.is_absolute() == true);
        }
    }
    SECTION("Relative") {
        SECTION("'.'") {
            Path current_without_slash{"."};
            REQUIRE(current_without_slash.size() == 0);
            REQUIRE(current_without_slash.is_absolute() == false);
        }
        SECTION("'..'") {
            Path parent{"../"};
            REQUIRE(parent.size() == 1);
            REQUIRE(parent.is_absolute() == false);
        }
        SECTION("'.' doesn't increase length") {
            Path current_inbetween{"path/./to/dir"};
            REQUIRE(current_inbetween.size() == 3);
            REQUIRE(current_inbetween.is_absolute() == false);
        }
    }
    SECTION("Empty") {
        REQUIRE_THROWS(Path(""));
    }
    SECTION("Empty filename") {
        REQUIRE_THROWS(Path("/path/to/empty//dir"));
    }
}

TEST_CASE("Path methods") {
    SECTION("Converting to string") {
        REQUIRE(Path{"/"}.string() == "/");

        const char* usr_local_bin = "/usr/local/bin/";
        REQUIRE(Path{"/usr/local/bin"}.string() == usr_local_bin);
        REQUIRE(Path{"/usr/local/bin/"}.string() == usr_local_bin);
        REQUIRE(Path{"/usr/local/bin/."}.string() == usr_local_bin);
        REQUIRE(Path{"/usr/local/lib/../bin"}.string() == usr_local_bin);

        REQUIRE(Path{"../../1/filesystem/path/"}.string() == "../../1/filesystem/path/"); 
        REQUIRE(Path{"/tmp"}.string() == "/tmp/");
        REQUIRE(Path{"abc"}.string() == "abc/");
        REQUIRE(Path{"./"}.string() == "./");
    }

    SECTION("Joining") {
        SECTION("Same paths") {
            Path p{"path/to/dir"};
            REQUIRE(p.join_with(p).string() == "path/to/dir/path/to/dir/");
        }
    }

    SECTION("Relativizing") {
        SECTION("Same paths") {
            Path p{"/home/guest/"};
            REQUIRE(p.relativize(p).string() == "./");
        }
    }
}
