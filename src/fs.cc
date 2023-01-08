#include "fs.hh"
#include "errors.hh"
#include "os.hh"

#include <fstream>

int readFile(std::string const& path, std::string& content) {
    if (std::ifstream fileStream { path, std::ios::in }) {
        content.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
        return 0;
    } else {
        return PL_ERR_FILE_NOT_FOUND;
    }
}

std::string dir(std::string const& path) {
    const size_t pos = path.find_last_of(PL_SLASH);
    return path.substr(0, pos);
}

std::string join(std::string const& path1, std::string const& path2) {
    return path1 + PL_SLASH + path2;
}
