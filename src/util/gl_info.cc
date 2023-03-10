#include "util/gl_info.hh"
#include "errors.hh"

#include <GL/glew.h>

using namespace upl;

int upl::coutGlVersion() {
    GLint glMajorVersion = -1;
    GLint glMinorVersion = -1;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &glMinorVersion);

    if (glMajorVersion == -1 || glMinorVersion == -1) {
        CERR_PANIC("OpenGL version could not be obtained!");
        return PL_ERR_PANIC;
    }

    const GLubyte* glFullVersion = glGetString(GL_VERSION);
    if (glFullVersion == nullptr) {
        CERR_PANIC("Full OpenGL version could not be obtained!");
        return PL_ERR_PANIC;
    }

    std::cout << "OpenGL version: " << glMajorVersion << "." << glMinorVersion << std::endl;
    std::cout << "Full OpenGL version: " << glFullVersion << std::endl;

    return 0;
}

int upl::coutGlslVersion() {
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    if (glslVersion == nullptr) {
        CERR_PANIC("GLSF VERSION could not be obtained!");
        return PL_ERR_PANIC;
    }

    std::cout << "GLSF version: " << glslVersion << std::endl;

    return 0;
}

int upl::coutGlVendor() {
    const GLubyte* glVendor = glGetString(GL_VENDOR);

    if (glVendor == nullptr) {
        CERR_PANIC("OpenGL vendor could not be obtained!");
        return PL_ERR_PANIC;
    }

    std::cout << "OpenGL vendor: " << glVendor << std::endl;

    return 0;
}

int upl::coutGlRenderer() {
    const GLubyte* glRenderer = glGetString(GL_RENDERER);

    if (glRenderer == nullptr) {
        CERR_PANIC("OpenGL renderer could not be obtained!");
        return PL_ERR_PANIC;
    }

    std::cout << "OpenGL vendor: " << glRenderer << std::endl;

    return 0;
}

int upl::coutAllInfo() {
    int err = 0;

    err = coutGlVersion();
    if (err != 0)
        return err;

    err = coutGlslVersion();
    if (err != 0)
        return err;

    err = coutGlVendor();
    if (err != 0)
        return err;

    err = coutGlRenderer();
    if (err != 0)
        return err;

    return 0;
}
