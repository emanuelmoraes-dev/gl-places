#ifndef _PL_SHADERS_HH_INCLUDED_
#define _PL_SHADERS_HH_INCLUDED_

#include "env.hh"
#include "util/os.hh"

#include <string>

#include <GL/glew.h>

#define PL_SHADER_VERT_ECHO PL_ENV_SHADERS_DIR PL_SLASH "echo_vert.glsl"
#define PL_SHADER_FRAG_ECHO PL_ENV_SHADERS_DIR PL_SLASH "echo_frag.glsl"

namespace opl {
    int loadShaders(GLuint* programId, std::string const& vertShaderFile, std::string const& fragShaderFile);
}

#endif
