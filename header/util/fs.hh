#ifndef _GL_PLACES_FS_HH_INCLUDED_
#define _GL_PLACES_FS_HH_INCLUDED_

#include <string>

int readFile(std::string const& path, std::string& content);
void dir(std::string const& file, std::string& content);
void join(std::string const& path1, std::string const& path2, std::string& content);
void getBinaryPath(int argc, const char* argv[], std::string& content);

#endif
