#ifndef _GL_PLACES_FS_HH_INCLUDED_
#define _GL_PLACES_FS_HH_INCLUDED_

#include <string>

int readFile(std::string const& path, std::string const& content);
std::string dir(std::string const& file);
std::string join(std::string const& path1, std::string const& path2);

#endif
