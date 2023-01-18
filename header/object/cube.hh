#ifndef _PL_OBJECT_CUBE_HH_INCLUDED_
#define _PL_OBJECT_CUBE_HH_INCLUDED_

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace opl {
    struct Cube {
        std::array<glm::vec3, 4> back;
        std::array<glm::vec3, 4> front;
        std::array<glm::vec3, 4> left;
        std::array<glm::vec3, 4> right;
        std::array<glm::vec3, 4> botton;
        std::array<glm::vec3, 4> top;
    };

    int loadCubeSideZ(std::array<glm::vec3, 4>& positions, float translate, bool rotateEnabled);
    int loadCubeSideX(std::array<glm::vec3, 4>& positions, float translate, bool rotateEnabled);
    int loadCubeSideY(std::array<glm::vec3, 4>& positions, float translate, bool rotateEnabled);

    int loadCube(Cube& cube, bool rotateEnabled);
    int loadCube(Cube& cube, std::array<GLuint, 6>& elements, bool rotateEnabled);
    int loadCube(std::array<glm::vec3, 8>& positions, bool rotateEnabled);
}

#endif
