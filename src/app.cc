#include "app.hh"
#include "errors.hh"
#include "util/fs.hh"

#include "object/shaders.hh"
#include "object/data.hh"

#include <nlohmann/json.hpp>
#include <fstream>

using namespace pl;
using namespace upl;
using namespace opl;

using json = nlohmann::json;

int loadShaders(App& app) {
    std::string vertShader;
    std::string fragShader;

    join(app.binaryPath, PL_SHADER_VERT_ECHO, vertShader);
    join(app.binaryPath, PL_SHADER_FRAG_ECHO, fragShader);
    int err = loadShaders(&(app.shaders.echo), vertShader, fragShader);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SHADERS, err, "Echo Program Error");
        return err;
    }

    join(app.binaryPath, PL_SHADER_VERT_LINE, vertShader);
    join(app.binaryPath, PL_SHADER_FRAG_LINE, fragShader);
    err = loadShaders(&(app.shaders.line), vertShader, fragShader);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SHADERS, err, "Echo Program Error");
        return err;
    }

    return 0;
}

int pl::loadApp(App& app, int argc, const char* argv[]) {
    getBinaryPath(argc, argv, app.binaryPath);

    int err = loadShaders(app);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SHADERS, err, "Error loading app shaders");
        return err;
    }

    if (std::ifstream configFile { PL_APP_CONFIG_FILE, std::ios::in }) {
        app.config = json::parse(configFile);
    } else {
        CERR_MSG(PL_ERR_LOAD_CONFIG_FILE, 1, PL_APP_CONFIG_FILE);
        return 1;
    }

    return 0;
}
