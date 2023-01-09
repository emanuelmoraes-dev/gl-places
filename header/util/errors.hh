#ifndef _GL_PLACES_ERRORS_HH_INCLUDED_
#define _GL_PLACES_ERRORS_HH_INCLUDED_

#include <iostream>

#define CERR(BME, CAUSE) std::cerr << "[Error " << BME << "/" << CAUSE << "]: " << BME##_MESSAGE << std::endl
#define CERR_MSG(BME, CAUSE, MSG) std::cerr << "[Error " << BME << "/" << CAUSE << "]: " << BME##_MESSAGE << ": " << MSG << std::endl
#define CERR_PANIC(MESSAGE) std::cerr << "[Panic]: " << MESSAGE << std::endl

#define __PL_ERRBASE (30) // internal errors should to start in 30

#define PL_ERR_PANIC (__PL_ERRBASE + 0)

#define PL_ERR_GLFW_INIT (__PL_ERRBASE + 1)
#define PL_ERR_GLFW_INIT_MESSAGE "GLFW wasn't initialized"

#define PL_ERR_WINDOW (__PL_ERRBASE + 2)
#define PL_ERR_WINDOW_MESSAGE "The window wasn't created"

#define PL_ERR_GLEW_INIT (__PL_ERRBASE + 3)
#define PL_ERR_GLEW_INIT_MESSAGE "GLEW wasn't initialized"

#define PL_ERR_FILE_NOT_FOUND (__PL_ERRBASE + 4)
#define PL_ERR_FILE_NOT_FOUND_MESSAGE "File not found"

#define PL_ERR_LOAD_SHADERS (__PL_ERRBASE + 5)
#define PL_ERR_LOAD_SHADERS_MESSAGE "Error loading program"

#define PL_ERR_SHADER_COMPILE_PANIC (__PL_ERRBASE + 6)
#define PL_ERR_SHADER_COMPILE_PANIC_MESSAGE "Compile shader fails without logs"

#define PL_ERR_SHADER_COMPILE (__PL_ERRBASE + 7)
#define PL_ERR_SHADER_COMPILE_MESSAGE "Shader failed"

#define PL_ERR_VERT_SHADER_COMPILE (__PL_ERRBASE + 8)
#define PL_ERR_VERT_SHADER_COMPILE_MESSAGE "Vertex shader failed"

#define PL_ERR_FRAG_SHADER_COMPILE (__PL_ERRBASE + 9)
#define PL_ERR_FRAG_SHADER_COMPILE_MESSAGE "Fragment shader failed"

#define PL_ERR_LINK_PROGRAM_PANIC (__PL_ERRBASE + 10)
#define PL_ERR_LINK_PROGRAM_PANIC_MESSAGE "Error linking program without logs"

#define PL_ERR_LINK_PROGRAM (__PL_ERRBASE + 11)
#define PL_ERR_LINK_PROGRAM_MESSAGE "Error linking program"

#define PL_ERR_STBI_LOAD (__PL_ERRBASE + 12)
#define PL_ERR_STBI_LOAD_MESSAGE "stb: Error loading image"

#define PL_ERR_LOAD_TEXTURE (__PL_ERRBASE + 13)
#define PL_ERR_LOAD_TEXTURE_MESSAGE "Error loading texture"

#define PL_ERR_LOAD_SCENE (__PL_ERRBASE + 14)
#define PL_ERR_LOAD_SCENE_MESSAGE "Error loading museum"

#define PL_ERR_DRAW_SCENE (__PL_ERRBASE + 15)
#define PL_ERR_DRAW_SCENE_MESSAGE "Error drawing museum"

#endif
