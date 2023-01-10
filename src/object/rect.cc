#include "object/rect.hh"
#include "util/errors.hh"

int loadRect(Vao& vao, float aspect) {
    int err = 0;
    if (aspect < 0.0f) {
        CERR_MSG(PL_ERR_NUMBER_MUST_BE_POSITIVE, PL_ERR_NUMBER_MUST_BE_POSITIVE, "aspect in loadRect() must be positive");
        return err;
    }

    float fx = 1.0f;
    float fy = 1.0f;

    if (aspect > 1.0f) {
        fy = 1.0f / aspect;
    } else {
        fx = aspect;
    }

    const glm::vec3 a{ -1.0f * fx, -1.0f * fy, 0.0f };
    const glm::vec3 b{  1.0f * fx, -1.0f * fy, 0.0f };
    const glm::vec3 c{ -1.0f * fx,  1.0f * fy, 0.0f };
    const glm::vec3 d{  1.0f * fx,  1.0f * fy, 0.0f };

    const Vertex vertexes[] = { Vertex{a}, Vertex{b}, Vertex{c}, Vertex{d} };
    const GLuint elements[] = {
        0, 1, 2,
        1, 2, 3
    };

    loadVAO(vao, 4, vertexes, 6, elements);

    return 0;
}
