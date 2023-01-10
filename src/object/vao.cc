#include "object/vao.hh"

void loadVBO(GLuint* vbo, GLsizeiptr size, const void* vertexBuffer) {
    glGenBuffers(1, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertexBuffer, GL_STATIC_DRAW);

    glBindBuffer(*vbo, 0);
}

void loadEBO(GLuint* ebo, GLsizeiptr size, const void* elementBuffer) {
    glGenBuffers(1, ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elementBuffer, GL_STATIC_DRAW);

    glBindBuffer(*ebo, 0);
}

Vao::~Vao() {
    if (this->id != 0) {
        glDeleteVertexArrays(1, &(this->id));
        this->id = 0;
    }
}

Vao::Vao() :
    id(0),
    vn(0),
    in(0)
    {}

void loadVAO(Vao& vao, GLsizei vn, const Vertex* vertexes, GLsizei in, const GLuint* elements) {
    vao.vn = vn;
    vao.in = in;

    GLuint vbo = 0;
    loadVBO(&vbo, sizeof(Vertex) * vn, vertexes);

    GLuint ebo = 0;
    loadEBO(&ebo, sizeof(GLsizei) * in, elements);

    glGenVertexArrays(1, &(vao.id));
    glBindVertexArray(vao.id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glBindVertexArray(0);
}
