#include "scene/museum.hh"
#include "object/shaders.hh"
#include "util/fs.hh"
#include "util/errors.hh"

#include <string>

#include <GL/glew.h>

Museum::~Museum() {
    glUseProgram(0);
    glDeleteProgram(this->walls.programId);
    glDeleteVertexArrays(1, &(this->walls.vao.id));
    glDeleteTextures(1, &(this->walls.textureId));
}

int museumLoad(Museum& museum, App const& app) {
    museum.light.direction = glm::vec3{ 0.0f, 0.0f, -1.0f };
    museum.light.intensity = 1.0f;
    museum.walls.textureId = 0;

    int err = 0;

    std::string vertShader;
    join(app.binaryPath, PL_SHADER_VERT_ECHO, vertShader);

    std::string fragShader;
    join(app.binaryPath, PL_SHADER_FRAG_ECHO, fragShader);

    err = loadShaders(&museum.walls.programId, vertShader, fragShader);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SHADERS, err, "Museum Program Error");
        return err;
    }

    return 0;
}

int museumDraw(Museum const& museum, World const& world) {
    return 0;
}
