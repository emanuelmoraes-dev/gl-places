#include "scene/museum.hh"

#include "errors.hh"

#include "object/shaders.hh"
#include "object/rect.hh"

#include "util/fs.hh"

#include <string>

#include <GL/glew.h>

const glm::mat4 I = glm::identity<glm::mat4>();

MuseumWalls::MuseumWalls() :
    programId(0),
    textureId(0),
    model(I) {}

MuseumWalls::~MuseumWalls() {
    glUseProgram(0);
    if (this->programId != 0) {
        glDeleteProgram(this->programId);
        this->programId = 0;
    }
    if (this->textureId != 0) {
        glDeleteTextures(1, &(this->textureId));
        this->textureId = 0;
    }
    this->vao.~Vao();
}

int loadWalls(MuseumWalls& walls, App const& app) {
    int err = 0;

    std::string vertShader;
    join(app.binaryPath, PL_SHADER_VERT_ECHO, vertShader);

    std::string fragShader;
    join(app.binaryPath, PL_SHADER_FRAG_ECHO, fragShader);

    err = loadShaders(&walls.programId, vertShader, fragShader);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SHADERS, err, "Museum Program Error");
        return err;
    }

    err = loadRect(walls.vao, 1.0f);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading rect");
        return err;
    }

    walls.model = glm::scale(walls.model, glm::vec3{ 0.5f, 0.5f, 0.0f });

    return 0;
}

int loadMuseum(Museum& museum, App const& app) {
    int err = loadWalls(museum.walls, app);

    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading museum walls");
        return err;
    }

    return 0;
}

int drawWalls(MuseumWalls const& walls, glm::mat4 const& world) {
    glUseProgram(walls.programId);

    const glm::mat4 mvp = walls.model * world;
    const GLint MVP = glGetUniformLocation(walls.programId, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(mvp));

    const glm::vec4 color{ 1.0f, 0.0f, 0.0f, 1.0f };
    const GLint COLOR = glGetUniformLocation(walls.programId, "COLOR");
    glUniform4fv(COLOR, 1, glm::value_ptr(color));

    glBindVertexArray(walls.vao.id);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, walls.vao.in, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);

    return 0;
}

int drawMuseum(Museum const& museum, glm::mat4 const& world) {
    int err = drawWalls(museum.walls, world);

    if (err != 0) {
        CERR_MSG(PL_ERR_DRAW_OBJECT, err, "Error drawing museum walls");
        return err;
    }

    return 0;
}
