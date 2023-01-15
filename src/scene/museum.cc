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

    array<array<glm::vec3, 4>, 6> boxPositions;
    array<array<GLuint, 6>, 6> boxElements;
    err = loadCube(boxPositions, boxElements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading box");
        return err;
    }

    // walls object
    VAOTarget target;
    GLsizei vertexOffset = 0;
    OPL_ATTACH(target, boxPositions[0], boxElements[0], &vertexOffset, gray); // back
    OPL_ATTACH(target, boxPositions[1], boxElements[1], &vertexOffset, gray); // right
    OPL_ATTACH(target, boxPositions[2], boxElements[2], &vertexOffset, gray); // front
    OPL_ATTACH(target, boxPositions[3], boxElements[3], &vertexOffset, gray); // left
    OPL_ATTACH(target, boxPositions[4], boxElements[4], &vertexOffset, beige); // top
    OPL_ATTACH(target, boxPositions[5], boxElements[5], &vertexOffset, whiteGray); // botton
    loadVAO(walls.object, target);

    // walls border
    clearVAOTarget(target, &vertexOffset);
    array<GLuint, 8> borderElements;
    err = loadSquareBorder(borderElements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading square border");
        return err;
    }
    OPL_ATTACH(target, boxPositions[0], borderElements, &vertexOffset, white); // back
    OPL_ATTACH(target, boxPositions[1], borderElements, &vertexOffset, white); // right
    OPL_ATTACH(target, boxPositions[2], borderElements, &vertexOffset, white); // front
    OPL_ATTACH(target, boxPositions[3], borderElements, &vertexOffset, white); // left
    OPL_ATTACH(target, boxPositions[4], borderElements, &vertexOffset, white); // top
    OPL_ATTACH(target, boxPositions[5], borderElements, &vertexOffset, white); // botton
    loadVAO(walls.border, target);

    const glm::vec3 scaleObject{ 9.0f, 4.0f, 16.0f };
    const glm::vec3 scaleInsideBorder = scaleObject - 0.01f;
    const glm::vec3 scaleOutsideBorder = scaleObject + 0.01f;

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
