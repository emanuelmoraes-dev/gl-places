#ifndef _PL_UTIL_FS_HH_INCLUDED_
#define _PL_UTIL_FS_HH_INCLUDED_

#include <string>
#include "util/os.hh"

#define UPL_JOIN(path1, path2) path1 PL_SLASH path2

namespace upl {
    int readFile(std::string const& path, std::string& content);
    void dir(std::string const& file, std::string& content);
    void join(std::string const& path1, std::string const& path2, std::string& content);
    void getBinaryPath(int argc, const char* argv[], std::string& content);
}

#endif
