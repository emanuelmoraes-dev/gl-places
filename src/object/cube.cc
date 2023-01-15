#include "object/cube.hh"
#include "object/square.hh"

#include "errors.hh"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace opl;
using namespace std;

const glm::mat4 I = glm::identity<glm::mat4>();

int opl::loadCubeSideZ(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements, float translate) {
    int err = 0;

    err = loadSquare(positions, elements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading rect");
        return err;
    }

    const glm::vec3 Y{ 0.0f, 1.0f, 0.0f };
    const float rotateAngle = translate > 0
        ? glm::radians(180.0f)
        : glm::radians(0.0f);
    const glm::mat4 rotateMatrix = glm::rotate(I, rotateAngle, Y);

    for (int i = 0; i < positions.size(); i++) {
        positions[i] = rotateMatrix * glm::vec4{ positions[i], 1.0f };
    }

    const glm::vec3 translateVector{ 0.0f, 0.0f, translate };
    const glm::mat4 translateMatrix = glm::translate(I, translateVector);

    for (int i = 0; i < positions.size(); i++) {
        positions[i] = translateMatrix * glm::vec4{ positions[i], 1.0f };
    }

    return 0;
}

int opl::loadCubeSideX(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements, float translate) {
    int err = 0;

    err = loadSquare(positions, elements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading rect");
        return err;
    }

    const glm::vec3 Y{ 0.0f, 1.0f, 0.0f };
    const float rotateAngle = translate > 0
        ? glm::radians(-90.0f)
        : glm::radians(90.0f);
    const glm::mat4 rotateMatrix = glm::rotate(I, rotateAngle, Y);

    for (int i = 0; i < positions.size(); i++) {
        positions[i] = rotateMatrix * glm::vec4{ positions[i], 1.0f };
    }

    const glm::vec3 translateVector{ translate, 0.0f, 0.0f };
    const glm::mat4 translateMatrix = glm::translate(I, translateVector);

    for (int i = 0; i < positions.size(); i++) {
        positions[i] = translateMatrix * glm::vec4{ positions[i], 1.0f };
    }

    return 0;
}

int opl::loadCubeSideY(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements, float translate) {
    int err = 0;

    err = loadSquare(positions, elements);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading rect");
        return err;
    }

    const glm::vec3 X{ 1.0f, 0.0f, 0.0f };
    const float rotateAngle = translate > 0
        ? glm::radians(90.0f)
        : glm::radians(-90.0f);
    const glm::mat4 rotateMatrix = glm::rotate(I, rotateAngle, X);

    for (int i = 0; i < positions.size(); i++) {
        positions[i] = rotateMatrix * glm::vec4{ positions[i], 1.0f };
    }

    const glm::vec3 translateVector{ 0.0f, translate, 0.0f };
    const glm::mat4 translateMatrix = glm::translate(I, translateVector);

    for (int i = 0; i < positions.size(); i++) {
        positions[i] = translateMatrix * glm::vec4{ positions[i], 1.0f };
    }

    return 0;
}

int opl::loadCube(std::array<std::array<glm::vec3, 4>, 6>& positions, std::array<std::array<GLuint, 6>, 6>& elements) {
    int err = 0;
    constexpr float translate = 1;

    err = loadCubeSideZ(positions[0], elements[0], -translate);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading back rect");
        return err;
    }

    err = loadCubeSideX(positions[1], elements[1], translate);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading right rect");
        return err;
    }

    err = loadCubeSideZ(positions[2], elements[2], translate);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading front rect");
        return err;
    }

    err = loadCubeSideX(positions[3], elements[3], -translate);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading left rect");
        return err;
    }

    err = loadCubeSideY(positions[4], elements[4], translate);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading top rect");
        return err;
    }

    err = loadCubeSideY(positions[5], elements[5], -translate);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_OBJECT, err, "Error loading botton rect");
        return err;
    }

    return 0;
}
