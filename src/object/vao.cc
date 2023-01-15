#include "object/vao.hh"

using namespace opl;

void opl::loadVBO(GLuint* vbo, GLsizeiptr size, const void* vertexBuffer) {
    glGenBuffers(1, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertexBuffer, GL_STATIC_DRAW);

    glBindBuffer(*vbo, 0);
}

void opl::loadEBO(GLuint* ebo, GLsizeiptr size, const void* elementBuffer) {
    glGenBuffers(1, ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elementBuffer, GL_STATIC_DRAW);

    glBindBuffer(*ebo, 0);
}

void opl::clearVAOTarget(VAOTarget& target, GLsizei* vertexOffset) {
    target.vertexes.clear();
    target.elements.clear();
    *vertexOffset = 0;
}

void opl::attach(
    VAOTarget& target,
    size_t pn,
    glm::vec3* positions,
    size_t en,
    GLuint* elements,
    GLsizei* vertexOffset,
    glm::vec3 color
) {
    for (int i = 0; i < pn; i++) {
        glm::vec3 position = positions[i];
        target.vertexes.push_back(Vertex{ position, color });
    }

    const GLsizei offset = *vertexOffset;

    for (int i = 0; i < en; i++) {
        const GLsizei element = elements[i];
        target.elements.push_back(offset + element);
    }

    *vertexOffset += (GLsizei) pn;
}

opl::Vao::~Vao() {
    if (this->id != 0) {
        glDeleteVertexArrays(1, &(this->id));
        this->id = 0;
    }
}

opl::Vao::Vao() :
    id(0),
    vn(0),
    en(0)
    {}

void opl::loadVAO(Vao& vao, GLsizei vn, const Vertex* vertexes, GLsizei en, const GLuint* elements) {
    vao.vn = vn;
    vao.en = en;

    GLuint vbo = 0;
    loadVBO(&vbo, sizeof(Vertex) * vn, vertexes);

    GLuint ebo = 0;
    loadEBO(&ebo, sizeof(GLsizei) * en, elements);

    glGenVertexArrays(1, &(vao.id));
    glBindVertexArray(vao.id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex),
        (const void*) offsetof(Vertex, color));

    glBindVertexArray(0);
}

void opl::loadVAO(Vao& vao, VAOTarget const& target) {
    loadVAO(vao, (GLsizei) target.vertexes.size(), target.vertexes.data(), (GLsizei) target.elements.size(), target.elements.data());
}
