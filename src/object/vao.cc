#include "object/vao.hh"
#include "util/cond.hh"

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

opl::Vertex::Vertex(glm::vec3 position, glm::vec3 color):
    position(position),
    color(color),
    uv(glm::vec2{ 0.0f, 0.0f }) {}

opl::Vertex::Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 uv):
    position(position),
    color(color),
    uv(uv) {}

opl::VAOTarget::VAOTarget() : vertexOffset(0) {}

void opl::clearVAOTarget(VAOTarget& target) {
    target.vertexes.clear();
    target.elements.clear();
    target.vertexOffset = 0;
}

void opl::vside(std::vector<Vertex>& vertexes, GLsizei pn, const glm::vec3* positions, glm::vec3 color, glm::vec2* uvs) {
    for (GLsizei p = 0; p < pn; p++) {
        const glm::vec2* uv = UPL_NULLABLE(uvs, uvs + p);
        glm::vec3 position = positions[p];

        if (uv != nullptr) {
            vertexes.push_back(Vertex{ position, color, *uv });
        } else {
            vertexes.push_back(Vertex{ position, color });
        }
    }
}

void opl::eside(std::vector<GLuint>& targetElements, GLsizei* vertexOffset, GLsizei count, GLsizei pn, GLsizei en, const GLuint* elements) {
    for (GLsizei c = 0; c < count; c++) {
        const GLsizei offset = *vertexOffset;

        for (GLsizei e = 0; e < en; e++) {
            const GLsizei element = elements[e];
            targetElements.push_back(offset + element);
        }

        *vertexOffset = (*vertexOffset) + pn;
    }
}

void opl::side(VAOTarget& target, GLsizei pn, const glm::vec3* positions, GLsizei en, const GLuint* elements, glm::vec3 color, glm::vec2* uvs) {
    vside(target.vertexes, pn, positions, color, uvs);
    eside(target.elements, &(target.vertexOffset), 1, pn, en, elements);
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

void opl::loadVAO(Vao& vao, GLsizei vn, GLuint vbo, GLsizei en, GLuint ebo) {
    vao.vbo = vbo;
    vao.ebo = ebo;
    vao.vn = vn;
    vao.en = en;

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

void opl::loadVAO(Vao& vao, GLsizei vn, const Vertex* vertexes, GLsizei en, const GLuint* elements) {
    GLuint vbo = 0;
    loadVBO(&vbo, sizeof(Vertex) * vn, vertexes);

    GLuint ebo = 0;
    loadEBO(&ebo, sizeof(GLsizei) * en, elements);

    loadVAO(vao, vn, vbo, en, ebo);
}

void opl::loadVAO(Vao& vao, VAOTarget const& target) {
    loadVAO(vao, (GLsizei) target.vertexes.size(), target.vertexes.data(), (GLsizei) target.elements.size(), target.elements.data());
}
