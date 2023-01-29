#include "scene/museum.hh"

#include "errors.hh"
#include "config.hh"

#include "object/shaders.hh"
#include "object/cube.hh"
#include "object/square.hh"

#include "util/fs.hh"
#include "util/border.hh"

#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <nlohmann/json.hpp>

using namespace pl;
using namespace opl;
using namespace spl;
using namespace upl;
using namespace std;

using json = nlohmann::json;

const glm::mat4 I = glm::identity<glm::mat4>();
const glm::vec3 red{ 1.0f, 0.0f, 0.0f };
const glm::vec3 blue{ 0.0f, 0.0f, 1.0f };
const glm::vec3 yellow{ 1.0f, 1.0f, 0.0f };
const glm::vec3 ciano{ 0.0f, 1.0f, 1.0f };
const glm::vec3 black{ 0.0f, 0.0f, 0.0f };
const glm::vec3 white{ 1.0f, 1.0f, 1.0f };
const glm::vec3 whiteGray{ 0.8f, 0.8f, 0.8f };
const glm::vec3 beige{ 0.73f, 0.58f, 0.41f };
const glm::vec3 gray{ 0.5f, 0.5f, 0.5f };

spl::MuseumWalls::MuseumWalls() :
    textureId(0),
    objectModel(I),
    insideBorderModel(I),
    outsideBorderModel(I) {}

spl::MuseumWalls::~MuseumWalls() {
    if (this->textureId != 0) {
        glDeleteTextures(1, &(this->textureId));
        this->textureId = 0;
    }
}

int loadWallsObject(Vao& wallsObject, Cube& cube) {
    // load cube
    array<GLuint, 6> cubeElements;
    int err = loadCube(cube, cubeElements, true);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading cube");
        return err;
    }

    // walls object
    VAOTarget target;
    OPL_SIDE(target, cube.back, cubeElements, gray);
    OPL_SIDE(target, cube.front, cubeElements, gray);
    OPL_SIDE(target, cube.left, cubeElements, gray);
    OPL_SIDE(target, cube.right, cubeElements, gray);
    OPL_SIDE(target, cube.botton, cubeElements, whiteGray);
    // OPL_SIDE(target, cube.top, cubeElements, beige);
    loadVAO(wallsObject, target);

    return 0;
}

int loadWallsBorder(Vao& wallsBorder, Cube const& cube) {
    // load border positions
    array<glm::vec3, 8> borderPositions;
    int err = loadCube(borderPositions, false);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading cube border positions");
        return err;
    }

    // load square border
    array<GLuint, 8> squareBorderElements;
    err = loadSquareBorder(squareBorderElements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading square border");
        return err;
    }

    // load square border glue
    const GLsizei sidePositions = (GLsizei) cube.back.size();
    vector<GLuint> glueSquareBorderElements;
    UPL_JOIN_BORDERS(glueSquareBorderElements, sidePositions, squareBorderElements, squareBorderElements);

    // walls border
    VAOTarget target;
    opl::vside(target.vertexes, sidePositions, borderPositions.data()                , white); // back border
    opl::vside(target.vertexes, sidePositions, borderPositions.data() + sidePositions, white); // front border
    OPL_ESIDE(target.elements, &(target.vertexOffset), 2, sidePositions, squareBorderElements); // back and front border
    target.elements.insert(target.elements.end(), glueSquareBorderElements.begin(), glueSquareBorderElements.end());   // glue border
    loadVAO(wallsBorder, target);

    return err;
}

int loadWalls(MuseumWalls& walls, App const& app) {
    Cube cube;

    int err = loadWallsObject(walls.object, cube);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading walls object");
        return err;
    }

    err = loadWallsBorder(walls.border, cube);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading walls border");
        return err;
    }

    // models

    const glm::vec3 scaleObject{ 9.0f, 4.0f, 16.0f };
    const glm::vec3 scaleInsideBorder = scaleObject + glm::vec3{ -0.01f };
    const glm::vec3 scaleOutsideBorder = scaleObject + glm::vec3{ 0.01f };

    walls.objectModel = glm::scale(walls.objectModel, scaleObject);
    walls.insideBorderModel = glm::scale(walls.insideBorderModel, scaleInsideBorder);
    walls.outsideBorderModel = glm::scale(walls.outsideBorderModel, scaleOutsideBorder);

    return 0;
}

int loadMainRoomData(MuseumRoomData& main, App const& app) {
    json collections = app.config
        .value("scenes", json::object())
        .value("museum", json::object())
        .value("rooms", json::object())
        .value("main", json::array());

    std::string resourcePath;
    join(PL_ENV_DATA_DIR, "resource", resourcePath);

    for (json::iterator c = collections.begin(); c != collections.end(); ++c) {
        std::string collection = (*c).get<std::string>();

        std::string collectionPath;
        join(resourcePath, collection, collectionPath);

        std::string collectionConfigFile;
        join(collectionPath, collection + ".json", collectionConfigFile);

        if (std::ifstream configFile { collectionConfigFile, std::ios::in }) {
            json imgs = json::parse(configFile)
                .value("imgs", json::array());

            int index = 0;
            for (json::iterator it = imgs.begin(); it != imgs.end(); ++it) {
                std::string filename = (*it).value("name", "");

                if (filename.empty()) {
                    const std::string message = collectionConfigFile + "[" + std::to_string(index) + "].name not found!";
                    CERR_MSG(PL_ERR_LOAD_DATA_CONFIG_FILE, 2, message);
                    return 2;
                }

                std::string imagePath;
                join(collectionPath, filename, imagePath);
                main.imgs.push_back(imagePath);
                ++index;
            }
        } else {
            CERR_MSG(PL_ERR_LOAD_DATA_CONFIG_FILE, 1, collectionConfigFile);
            return 1;
        }
    }

    return 0;
}

int loadRooms(MuseumRooms& rooms, App const& app) {
    int err = loadMainRoomData(rooms.main, app);

    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_DATA, err, "Error loading museum main room data");
        return err;
    }

    for (std::string const& img : rooms.main.imgs) {
        std::cout << "Image: " << img << std::endl;
    }

    return 0;
}

int loadContent(MuseumContent& content, App const& app) {
    int err = loadRooms(content.rooms, app);

    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_DATA, err, "Error loading museum rooms content");
        return err;
    }

    return 0;
}

int spl::loadMuseum(Museum& museum, App const& app) {
    int err = loadWalls(museum.walls, app);

    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading museum walls");
        return err;
    }

    err = loadContent(museum.content, app);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_DATA, err, "Error loading museum content");
        return err;
    }

    return 0;
}

void drawWallsObject(MuseumWalls const& walls, App const& app, World const& world) {
    glUseProgram(app.shaders.echo);

    glm::mat4 model = world.model * walls.objectModel;
    glm::mat4 mvp = world.projection * world.view * model;
    echo::shaderUniform(app.shaders.echo, mvp);

    glBindVertexArray(walls.object.id);
    glDrawElements(GL_TRIANGLES, walls.object.en, GL_UNSIGNED_INT, nullptr);
}

void drawWallsBorder(MuseumWalls const& walls, App const& app, World const& world, glm::mat4 const& borderModel) {
    glUseProgram(app.shaders.echo);

    glm::mat4 model = world.model * borderModel;
    glm::mat4 mvp = world.projection * world.view * model;
    echo::shaderUniform(app.shaders.echo, mvp);

    glLineWidth(1.0f);
    glBindVertexArray(walls.border.id);
    glDrawElements(GL_LINES, walls.border.en, GL_UNSIGNED_INT, nullptr);
}

int drawWalls(MuseumWalls const& walls, App const& app, World const& world) {
    // setup
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // draw
    drawWallsObject(walls, app, world);
    drawWallsBorder(walls, app, world, walls.insideBorderModel);
    drawWallsBorder(walls, app, world, walls.outsideBorderModel);

    glBindVertexArray(0);
    glUseProgram(0);

    return 0;
}

int spl::drawMuseum(Museum const& museum, App const& app, World const& world) {
    int err = drawWalls(museum.walls, app, world);

    if (err != 0) {
        CERR_MSG(PL_ERR_DRAW_OBJECT, err, "Error drawing museum walls");
        return err;
    }

    return 0;
}
