#include "scene/museum.hh"

#include "errors.hh"

#include "object/shaders.hh"
#include "object/cube.hh"
#include "object/square.hh"

#include "util/fs.hh"

#include <string>
#include <vector>
#include <array>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace pl;
using namespace opl;
using namespace spl;
using namespace upl;
using namespace std;

const glm::mat4 I = glm::identity<glm::mat4>();

spl::MuseumWalls::MuseumWalls() :
    programId(0),
    textureId(0),
    objectModel(I),
    insideBorderModel(I),
    outsideBorderModel(I) {}

spl::MuseumWalls::~MuseumWalls() {
    glUseProgram(0);
    if (this->programId != 0) {
        glDeleteProgram(this->programId);
        this->programId = 0;
    }
    if (this->textureId != 0) {
        glDeleteTextures(1, &(this->textureId));
        this->textureId = 0;
    }
}

int loadWalls(MuseumWalls& walls, App const& app) {
    int err = 0;

    string vertShader;
    join(app.binaryPath, PL_SHADER_VERT_ECHO, vertShader);

    string fragShader;
    join(app.binaryPath, PL_SHADER_FRAG_ECHO, fragShader);

    err = loadShaders(&walls.programId, vertShader, fragShader);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SHADERS, err, "Museum Program Error");
        return err;
    }

    const glm::vec3 red{ 1.0f, 0.0f, 0.0f };
    const glm::vec3 blue{ 0.0f, 0.0f, 1.0f };
    const glm::vec3 yellow{ 1.0f, 1.0f, 0.0f };
    const glm::vec3 ciano{ 0.0f, 1.0f, 1.0f };
    const glm::vec3 black{ 0.0f, 0.0f, 0.0f };
    const glm::vec3 white{ 1.0f, 1.0f, 1.0f };
    const glm::vec3 whiteGray{ 0.8f, 0.8f, 0.8f };
    const glm::vec3 beige{ 0.73f, 0.58f, 0.41f };
    const glm::vec3 gray{ 0.5f, 0.5f, 0.5f };

    // load cube
    Cube cube;
    array<GLuint, 6> cubeElements;
    err = loadCube(cube, cubeElements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading cube");
        return err;
    }

    // walls object
    VAOTarget target;
    GLsizei vertexOffset = 0;
    OPL_ATTACH(target, cube.back, cubeElements, &vertexOffset, gray);
    OPL_ATTACH(target, cube.right, cubeElements, &vertexOffset, gray);
    OPL_ATTACH(target, cube.front, cubeElements, &vertexOffset, gray);
    OPL_ATTACH(target, cube.left, cubeElements, &vertexOffset, gray);
    OPL_ATTACH(target, cube.top, cubeElements, &vertexOffset, beige);
    OPL_ATTACH(target, cube.botton, cubeElements, &vertexOffset, whiteGray);
    loadVAO(walls.object, target);

    // walls border
    clearVAOTarget(target, &vertexOffset);
    array<GLuint, 8> borderElements;
    err = loadSquareBorder(borderElements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading square border");
        return err;
    }
    OPL_ATTACH(target, cube.back, borderElements, &vertexOffset, white);
    OPL_ATTACH(target, cube.right, borderElements, &vertexOffset, white);
    OPL_ATTACH(target, cube.front, borderElements, &vertexOffset, white);
    OPL_ATTACH(target, cube.left, borderElements, &vertexOffset, white);
    OPL_ATTACH(target, cube.top, borderElements, &vertexOffset, white);
    OPL_ATTACH(target, cube.botton, borderElements, &vertexOffset, white);
    loadVAO(walls.border, target);

    const glm::vec3 scaleObject{ 9.0f, 4.0f, 16.0f };
    const glm::vec3 scaleInsideBorder = scaleObject + glm::vec3{ -0.01f };
    const glm::vec3 scaleOutsideBorder = scaleObject + glm::vec3{ 0.01f };

    walls.objectModel = glm::scale(walls.objectModel, scaleObject);
    walls.insideBorderModel = glm::scale(walls.insideBorderModel, scaleInsideBorder);
    walls.outsideBorderModel = glm::scale(walls.outsideBorderModel, scaleOutsideBorder);

    return 0;
}

int spl::loadMuseum(Museum& museum, App const& app) {
    int err = loadWalls(museum.walls, app);

    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading museum walls");
        return err;
    }

    return 0;
}

int drawWalls(MuseumWalls const& walls, World const& world) {
    glUseProgram(walls.programId);

    // setup
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // walls object MVP
    glm::mat4 model = world.model * walls.objectModel;
    glm::mat4 mvp = world.projection * world.view * model;
    GLint MVP = glGetUniformLocation(walls.programId, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(mvp));

    // draw walls object
    glBindVertexArray(walls.object.id);
    glDrawElements(GL_TRIANGLES, walls.object.en, GL_UNSIGNED_INT, nullptr);

    // walls inside border MVP
    model = world.model * walls.insideBorderModel;
    mvp = world.projection * world.view * model;
    MVP = glGetUniformLocation(walls.programId, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(mvp));

    // draw walls inside border
    glLineWidth(1.0f);
    glBindVertexArray(walls.border.id);
    glDrawElements(GL_LINES, walls.border.en, GL_UNSIGNED_INT, nullptr);

    // walls outside border MVP
    model = world.model * walls.outsideBorderModel;
    mvp = world.projection * world.view * model;
    MVP = glGetUniformLocation(walls.programId, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(mvp));

    // draw walls outside border
    glLineWidth(1.0f);
    glBindVertexArray(walls.border.id);
    glDrawElements(GL_LINES, walls.border.en, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);

    return 0;
}

int spl::drawMuseum(Museum const& museum, World const& world) {
    int err = drawWalls(museum.walls, world);

    if (err != 0) {
        CERR_MSG(PL_ERR_DRAW_OBJECT, err, "Error drawing museum walls");
        return err;
    }

    return 0;
}
