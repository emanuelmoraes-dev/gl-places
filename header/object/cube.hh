#ifndef _PL_CUBE_HH_INCLUDED_
#define _PL_CUBE_HH_INCLUDED_

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace opl {
    int loadCubeSideZ(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements, float translate);
    int loadCubeSideX(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements, float translate);
    int loadCubeSideY(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements, float translate);
    int loadCube(std::array<std::array<glm::vec3, 4>, 6>& positions, std::array<std::array<GLuint, 6>, 6>& elements);
}

#endif
