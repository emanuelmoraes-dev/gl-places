#ifndef _PL_APP_HH_INCLUDED_
#define _PL_APP_HH_INCLUDED_

#include "object/shaders.hh"
#include "object/walk_camera.hh"

#include <string>
#include <nlohmann/json.hpp>

namespace pl {

    struct App {
        std::string binaryPath;
        opl::Shaders shaders;
        nlohmann::json config;

        const opl::WalkCamera* camera;
    };

    int loadApp(App& app, int argc, const char* argv[]);
}

#endif
