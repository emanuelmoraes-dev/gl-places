#ifndef _PL_VAO_HH_INCLUDED_
#define _PL_VAO_HH_INCLUDED_

#include <vector>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define OPL_ATTACH(target, positions, elements, vertexOffset, color) \
opl::attach(target, positions.size(), positions.data(), elements.size(), elements.data(), vertexOffset, color)

namespace opl {
    void loadVBO(GLuint* vbo, GLsizeiptr size, const void* vertexBuffer);
    void loadEBO(GLuint* ebo, GLsizeiptr size, const void* elementBuffer);

    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };

    struct VAOTarget {
        std::vector<Vertex> vertexes;
        std::vector<GLuint> elements;
    };

    void clearVAOTarget(VAOTarget& target, GLsizei* vertexOffset);

    void attach(
        VAOTarget& target,
        size_t pn,
        glm::vec3* positions,
        size_t en,
        GLuint* elements,
        GLsizei* vertexOffset,
        glm::vec3 color
    );

    struct Vao {
        GLuint id;
        GLsizei vn;
        GLsizei en;

        Vao();
        ~Vao();
    };

    void loadVAO(Vao& vao, GLsizei vn, const Vertex* vertexes, GLsizei en, const GLuint* elements);
    void loadVAO(Vao& vao, VAOTarget const& target);
}

#endif
