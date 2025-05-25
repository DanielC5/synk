# include <iostream>
# include <filesystem>
# include <string>

namespace fs = std::filesystem;

struct UserDirectories {
    fs::path source;
    fs::path target;
};


UserDirectories user_input(); 

//where function type is std::error_code, this will then be passed into 
// error_message where all error printing is centralized
[[nodiscard]] std::error_code print_directory(const fs::path& dir);
std::string error_message(const std::error_code& ec);
[[nodiscard]] std::error_code copy_directory(const fs::path& src, const fs::path& dst);

// Helper function to check and handle error_codes uniformly
int check_and_print_error(const std::error_code& ec) {
    if (ec) {
        std::cerr << error_message(ec) << '\n';
        return 1;
    }
    return 0;
}

int main() {
    UserDirectories dirs = user_input();

    std::error_code ec;
    // we use a single ec variable throughout, in the future if desired, 
    // we could use separate ec variables (e.g. ec_copy) for more readability/troubleshooting

    ec = copy_directory(dirs.source, dirs.target);
    if (check_and_print_error(ec)) return 1;

    std::cout << "Contents of " << dirs.source << " successfully copied to " << dirs.target << '\n';

    ec = print_directory(dirs.target);
    if (check_and_print_error(ec)) return 1;

    std::cout << "Copy succeeded!\n";
    return 0;
}

// Prompt user for source and target directories, return as UserDirectories type struct
UserDirectories user_input() {

    std::string source_input, target_input;

    UserDirectories initial_user_input;

    std::cout << "Welcome to synk!" << '\n';
    std::cout << "Please enter a source directory to copy from: ";

    getline(std::cin, source_input);
    initial_user_input.source = source_input;
    // std::cout << "Source Directory: " << initial_user_input.source << std::endl;
    // ^^ debug print statement to ensure directories are actually passed to variable; use if needed

    std::cout << "Please enter a target directory to copy to: ";
    getline(std::cin, target_input);
    initial_user_input.target = target_input;
    // std::cout << "Target Directory: " << initial_user_input.target << std::endl;
    // ^^ debug print statement to ensure directories are actually passed to variable; use if needed

    return initial_user_input;
}

std::error_code print_directory(const fs::path& directory) {
    if (!fs::exists(directory)) {
        return std::make_error_code(std::errc::no_such_file_or_directory);
    }

    std::error_code ec;
    for (const auto& dir_entry : fs::recursive_directory_iterator(directory, ec)) {
        if (ec) {
            return ec;
        } // If any error occurs during iteration of directories, exit early & return error code
        std::cout << dir_entry.path() << '\n';
    }

    return {}; // no error
}

// TODO: Refactor copying logic when doing bi-directional copying
// between machines with multiple folders instead of just
// between two local folders

std::error_code copy_directory(const fs::path& source, const fs::path& target) {
    if (!fs::exists(source)) {
        return std::make_error_code(std::errc::no_such_file_or_directory);
    }
    if (!fs::exists(target)) {
        return std::make_error_code(std::errc::no_such_file_or_directory);
    }

    std::error_code ec;
    fs::copy(source, target, fs::copy_options::recursive, ec);
    return ec;
}

// More readable error messages for user, add more common errors as necessary
std::string error_message(const std::error_code& ec) {
    switch (ec.value()) {
        case static_cast<int>(std::errc::no_such_file_or_directory):
            return "Error: One or more directories do not exist.";
        case static_cast<int>(std::errc::permission_denied):
            return "Error: Permission denied during file operation.";
        case static_cast<int>(std::errc::file_exists):
            return "Error: File or directory already exists at the destination.";
        case static_cast<int>(std::errc::not_a_directory):
            return "Error: Expected a directory but found a different file type.";
        case static_cast<int>(std::errc::io_error):
            return "Error: I/O error occurred during the operation.";
        case static_cast<int>(std::errc::device_or_resource_busy):
            return "Error: Device or resource is busy.";
        case static_cast<int>(std::errc::filename_too_long):
            return "Error: File name or path is too long.";
        default:
            return "Error: " + ec.message();
    }
}

