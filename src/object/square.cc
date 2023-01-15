#include "object/square.hh"
#include "errors.hh"

using namespace opl;

int opl::loadSquare(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements) {
    positions[0] = glm::vec3{ -1.0f, -1.0f, 0.0f };
    positions[1] = glm::vec3{  1.0f, -1.0f, 0.0f };
    positions[2] = glm::vec3{ -1.0f,  1.0f, 0.0f };
    positions[3] = glm::vec3{  1.0f,  1.0f, 0.0f };

    elements[0] = 0;
    elements[1] = 1;
    elements[2] = 2;
    elements[3] = 2;
    elements[4] = 1;
    elements[5] = 3;

    return 0;
}

int opl::loadSquareBorder(std::array<GLuint, 8>& elements) {
    elements[0] = 0;
    elements[1] = 1;

    elements[2] = 1;
    elements[3] = 3;

    elements[4] = 3;
    elements[5] = 2;

    elements[6] = 2;
    elements[7] = 0;
    return 0;
}
