#ifndef _PL_APP_HH_INCLUDED_
#define _PL_APP_HH_INCLUDED_

#include <string>

class App {
public:
    std::string binaryPath;

    App(int argc, const char* argv[]);
};

#endif
