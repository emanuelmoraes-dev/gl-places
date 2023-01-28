#ifndef _PL_OBJECT_SHADERS_HH_INCLUDED_
#define _PL_OBJECT_SHADERS_HH_INCLUDED_

#include "env.hh"
#include "util/fs.hh"

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define PL_SHADER_VERT_ECHO \
UPL_JOIN(PL_ENV_SHADERS_DIR, "echo_vert.glsl")

#define PL_SHADER_FRAG_ECHO \
UPL_JOIN(PL_ENV_SHADERS_DIR, "echo_frag.glsl")

#define PL_SHADER_VERT_LINE \
UPL_JOIN(PL_ENV_SHADERS_DIR, "line_vert.glsl")

#define PL_SHADER_FRAG_LINE \
UPL_JOIN(PL_ENV_SHADERS_DIR, "line_frag.glsl")

namespace opl {
    int loadShaders(GLuint* programId, std::string const& vertShaderFile, std::string const& fragShaderFile);

    struct Shaders {
        GLuint echo;
        GLuint line;

        Shaders();
        ~Shaders();
    };

    namespace echo {
        void shaderUniform(GLuint programId, glm::mat4 const& mvp);
    }

    namespace line {
        void shaderUniform(GLuint programId, glm::mat4 const& mvp, int viewPortWidth, int viewPortHeight, glm::vec4 const& color, float lineWidth, float blendFactor);
    }
}

#endif
