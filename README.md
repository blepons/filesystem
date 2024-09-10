
# Filesystem

A utility library for manipulating file paths.



## Dependencies

 - CMake
 - Catch2
 - gvocr

## Installation

To install the project, run the following commands
```bash
  mkdir build
  cd build
  cmake ..
  make
```
    
## Running Tests

To run tests, run the following commands

```bash
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=yes ..
  make unit_tests
  ./tests/unit_tests
```


## License

[BSD 3-Clause "New" or "Revised" License](https://choosealicense.com/licenses/bsd-3-clause/)

