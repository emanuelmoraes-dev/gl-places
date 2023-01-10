#include "util/fs.hh"
#include "util/os.hh"
#include "errors.hh"

#include <fstream>

int readFile(std::string const& path, std::string& content) {
    if (std::ifstream fileStream { path, std::ios::in }) {
        content.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
        return 0;
    } else {
        return PL_ERR_FILE_NOT_FOUND;
    }
}

void dir(std::string const& path, std::string& content) {
    const size_t pos = path.find_last_of(PL_SLASH);
    content = path.substr(0, pos);
}

void join(std::string const& path1, std::string const& path2, std::string& content) {
    content = path1 + PL_SLASH + path2;
}

void getBinaryPath(int argc, const char* argv[], std::string& content) {
    if (argc < 1) {
        content = ".";
    }
    dir(argv[0], content);
}
