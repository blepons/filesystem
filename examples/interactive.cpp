#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include "filesystem.hpp"

void clear_cin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void check_cin() {
    if (std::cin.eof()) {
        throw std::runtime_error("Unexpected EOF");
    }
    if (std::cin.bad()) {
        throw std::runtime_error("Input error");
    }
}

void handle_join() {
    std::string base, appended;
    std::cout << "Enter base path: ";
    std::getline(std::cin, base);
    check_cin();
    std::cout << "Enter appended path: ";
    std::getline(std::cin, appended);
    check_cin();

    try {
        std::cout << Filesystem::join(base, appended) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

void handle_absolute() {
    std::string path;
    std::cout << "Enter path: ";
    std::getline(std::cin, path);
    check_cin();

    try {
        std::cout << Filesystem::absolute(path) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

void handle_relativize() {
    std::string base, path;
    std::cout << "Enter base path: ";
    std::getline(std::cin, base);
    check_cin();
    std::cout << "Enter path: ";
    std::getline(std::cin, path);
    check_cin();

    try {
        std::cout << Filesystem::relativize(base, path) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

void handle_relative() {
    std::string path;
    std::cout << "Enter path: ";
    std::getline(std::cin, path);
    check_cin();

    try {
        std::cout << Filesystem::relative(path) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

int main() try {
    while (true) {
        std::cout << "Select a function:\n";
        std::cout << "1. join\n";
        std::cout << "2. absolute\n";
        std::cout << "3. relativize\n";
        std::cout << "4. relative\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.eof()) {
            return 0;
        }
        if (std::cin.fail()) {
            clear_cin();
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
        clear_cin();

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                handle_join();
                break;
            case 2:
                handle_absolute();
                break;
            case 3:
                handle_relativize();
                break;
            case 4:
                handle_relative();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    return 0;
} catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
}
