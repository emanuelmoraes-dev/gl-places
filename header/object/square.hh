#ifndef _PL_OBJECT_SQUARE_HH_INCLUDED_
#define _PL_OBJECT_SQUARE_HH_INCLUDED_

#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace opl {
    int loadSquare(std::array<glm::vec3, 4>& positions);
    int loadSquare(std::array<GLuint, 6>& elements);
    int loadSquare(std::array<glm::vec3, 4>& positions, std::array<GLuint, 6>& elements);
    int loadSquareBorder(std::array<GLuint, 8>& elements);
}

#endif
