#ifndef _PL_OBJECT_VAO_HH_INCLUDED_
#define _PL_OBJECT_VAO_HH_INCLUDED_

#include <vector>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define OPL_VSIDE(vertexes, positions, color) \
opl::vside(vertexes, (GLsizei) positions.size(), positions.data(), color)

#define OPL_ESIDE(targetElements, vertexOffset, count, pn, elements) \
opl::eside(targetElements, vertexOffset, count, pn, (GLsizei) elements.size(), elements.data())

#define OPL_SIDE(target, positions, elements, color) \
opl::side(target, (GLsizei) positions.size(), positions.data(), (GLsizei) elements.size(), elements.data(), color)

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
        GLsizei vertexOffset;

        VAOTarget();
    };

    void clearVAOTarget(VAOTarget& target);

    void vside(std::vector<Vertex>& vertexes, GLsizei pn, const glm::vec3* positions, glm::vec3 color);

    void eside(std::vector<GLuint>& targetElements, GLsizei* vertexOffset, GLsizei count, GLsizei pn, GLsizei en, const GLuint* elements);

    void side(VAOTarget& target, GLsizei pn, const glm::vec3* positions, GLsizei en, const GLuint* elements, glm::vec3 color);

    struct Vao {
        GLuint id;
        GLuint vbo;
        GLuint ebo;
        GLsizei vn;
        GLsizei en;

        Vao();
        ~Vao();
    };

    void loadVAO(Vao& vao, GLsizei vn, GLuint vbo, GLsizei en, GLuint ebo);
    void loadVAO(Vao& vao, GLsizei vn, const Vertex* vertexes, GLsizei en, const GLuint* elements);
    void loadVAO(Vao& vao, VAOTarget const& target);
}

#endif
