#include "app.hh"
#include "errors.hh"
#include "util/fs.hh"
#include "object/shaders.hh"

using namespace pl;
using namespace upl;
using namespace opl;

pl::App::~App() {
    glUseProgram(0);

    if (this->shaders.echo != 0) {
        glDeleteProgram(this->shaders.echo);
        this->shaders.echo = 0;
    }

    if (this->shaders.line != 0) {
        glDeleteProgram(this->shaders.line);
        this->shaders.line = 0;
    }
}

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

    return 0;
}
