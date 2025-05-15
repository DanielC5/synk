# include <iostream>
# include <filesystem>
# include <string>

int main() {
    using namespace std;
    namespace fs = std::filesystem;

    fs::path source;
    fs::path target;

    cout << "Welcome to synk!" << '\n';
    cout << "Please enter a source directory filepath: ";

    cin >> source;

    if (!fs::exists(source)) {
        std::cerr << "Source directory does not exist: " << source << '\n';
        return 1;
        }
    cout << "Please enter a target directory filepath: ";
    cin >> target;

    cout << '\n' << "Contents of " << source << ": \n";
    for (const fs::directory_entry& dir_entry:
        fs::recursive_directory_iterator(source)) {
        cout << dir_entry << '\n';
        }

    std::error_code ec;
    fs::copy(source, target, fs::copy_options::recursive, ec);

    if (ec) {
        cout << "Error: " << ec.message() << '\n';
    }

    else {
    cout << "Contents of " << source << " were successfully copied to " << target << " : \n\n";
    for (const fs::directory_entry& dir_entry:
        fs::recursive_directory_iterator(target)) {
        cout << dir_entry.path() << '\n';}
    }
    return 0;
}
