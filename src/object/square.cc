#include "object/square.hh"
#include "errors.hh"

using namespace opl;

int opl::loadSquare(std::array<glm::vec3, 4>& positions) {
    positions[0] = glm::vec3{ -1.0f, -1.0f, 0.0f };
    positions[1] = glm::vec3{  1.0f, -1.0f, 0.0f };
    positions[2] = glm::vec3{  1.0f,  1.0f, 0.0f };
    positions[3] = glm::vec3{ -1.0f,  1.0f, 0.0f };
    return 0;
}

int opl::loadSquare(std::array<GLuint, 6>& elements) {
    elements[0] = 0;
    elements[1] = 1;
    elements[2] = 3;
    elements[3] = 3;
    elements[4] = 1;
    elements[5] = 2;
    return 0;
}

int opl::loadSquareUV(std::array<glm::vec2, 4> uvs) {
    uvs[0] = glm::vec2{ 0.0f, 0.0f };
    uvs[1] = glm::vec2{ 1.0f, 0.0f };
    uvs[2] = glm::vec2{ 1.0f, 1.0f };
    uvs[3] = glm::vec2{ 0.0f, 1.0f };
    return 0;
}

int opl::loadSquare(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements) {
    int err = 0;

    err = loadSquare(positions);
    if (err != 0) {
        return err;
    }

    err = loadSquare(elements);
    if (err != 0) {
        return err;
    }

    return 0;
}

int opl::loadSquare(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements, std::array<glm::vec2, 4> uvs) {
    int err = loadSquare(positions, elements);
    if (err != 0) {
        return err;
    }

    err = loadSquareUV(uvs);
    if (err != 0) {
        return err;
    }

    return 0;
}

int opl::loadSquareBorder(std::array<GLuint, 8>& elements) {
    elements[0] = 0;
    elements[1] = 1;

    elements[2] = 1;
    elements[3] = 2;

    elements[4] = 2;
    elements[5] = 3;

    elements[6] = 3;
    elements[7] = 0;
    return 0;
}
