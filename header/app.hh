#ifndef _PL_APP_HH_INCLUDED_
#define _PL_APP_HH_INCLUDED_

#include "object/shaders.hh"
#include "object/walk_camera.hh"

#include <string>

namespace pl {

    struct App {
        std::string binaryPath;
        opl::Shaders shaders;
        const opl::WalkCamera* camera;

        ~App();
    };

    int loadApp(App& app, int argc, const char* argv[]);
}

#endif
