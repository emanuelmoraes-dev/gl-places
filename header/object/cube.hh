#ifndef _PL_CUBE_HH_INCLUDED_
#define _PL_CUBE_HH_INCLUDED_

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace opl {

    struct Cube {
        std::array<glm::vec3, 4> back;
        std::array<glm::vec3, 4> right;
        std::array<glm::vec3, 4> front;
        std::array<glm::vec3, 4> left;
        std::array<glm::vec3, 4> top;
        std::array<glm::vec3, 4> botton;
    };

    int loadCubeSideZ(std::array<glm::vec3, 4>& positions, float translate);
    int loadCubeSideX(std::array<glm::vec3, 4>& positions, float translate);
    int loadCubeSideY(std::array<glm::vec3, 4>& positions, float translate);
    int loadCube(Cube& cube);
    int loadCube(Cube& cube, std::array<GLuint, 6>& elements);
}

#endif
