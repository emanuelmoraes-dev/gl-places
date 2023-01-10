#ifndef _PL_VAO_HH_INCLUDED_
#define _PL_VAO_HH_INCLUDED_

#include <GL/glew.h>
#include <glm/glm.hpp>

void loadVBO(GLuint* vbo, GLsizeiptr size, const void* vertexBuffer);
void loadEBO(GLuint* ebo, GLsizeiptr size, const void* elementBuffer);

struct Vertex {
    glm::vec3 position;
};

struct Vao {
    GLuint id;
    GLsizei vn;
    GLsizei in;

    Vao();
    ~Vao();
};

void loadVAO(Vao& vao, GLsizei vn, const Vertex* vertexes, GLsizei in, const GLuint* elements);

#endif
