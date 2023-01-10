#include "object/shaders.hh"
#include "errors.hh"
#include "util/fs.hh"

#include <string>

int checkShader(GLuint shaderId) {
    GLint infoLogLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        GLint len = infoLogLength + 1;
        char* infoLog = new char[len];
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog);
        infoLog[infoLogLength] = '\0';
        std::cerr << std::endl << infoLog;
        delete[] infoLog;
    }

    GLint compileStatus = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        if (infoLogLength == 0) {
            CERR(PL_ERR_SHADER_COMPILE_PANIC, PL_ERR_SHADER_COMPILE_PANIC);
            return PL_ERR_SHADER_COMPILE_PANIC;
        }
        return PL_ERR_SHADER_COMPILE;
    }

    return 0;
}

int checkProgram(GLuint programId) {
    GLint infoLogLength = 0;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        GLint len = infoLogLength + 1;
        char* infoLog = new char[len];
        glGetProgramInfoLog(programId, infoLogLength, nullptr, infoLog);
        infoLog[infoLogLength] = '\0';
        std::cerr << infoLog;
        delete[] infoLog;
    }

    GLint linkStatus = GL_FALSE;
    glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE) {
        if (infoLogLength == 0) {
            CERR(PL_ERR_LINK_PROGRAM_PANIC, PL_ERR_LINK_PROGRAM_PANIC);
            return PL_ERR_LINK_PROGRAM_PANIC;
        }
        return PL_ERR_LINK_PROGRAM;
    }

    return 0;
}

void freeShaders(GLuint const* vertShaderId, GLuint const* fragShaderId, GLuint const* programId) {
    if (programId != nullptr) {
        if (vertShaderId != nullptr)
            glDetachShader(*programId, *vertShaderId);
        if (fragShaderId != nullptr)
            glDetachShader(*programId, *fragShaderId);
    }

    if (vertShaderId != nullptr)
        glDeleteShader(*vertShaderId);
    if (fragShaderId != nullptr)
        glDeleteShader(*fragShaderId);
}

void freeProgram(GLuint const* programId, GLuint const* vertShaderId, GLuint const* fragShaderId) {
    freeShaders(programId, vertShaderId, fragShaderId);
    glDeleteProgram(*programId);
}

int loadShaders(GLuint* const programId, std::string const& vertShaderFile, std::string const& fragShaderFile) {
    int err = 0;

    std::cout << "loading " << vertShaderFile << std::endl;
    std::string vertShaderSource;
    err = readFile(vertShaderFile, vertShaderSource);
    if (err != 0) {
        CERR(PL_ERR_FILE_NOT_FOUND, err);
        return PL_ERR_FILE_NOT_FOUND;
    }

    GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    const char* vertShaderSourcePtr = vertShaderSource.c_str();
    glShaderSource(vertShaderId, 1, &vertShaderSourcePtr, nullptr);
    glCompileShader(vertShaderId);
    err = checkShader(vertShaderId);
    if (err != 0) {
        CERR(PL_ERR_VERT_SHADER_COMPILE, err);
        freeShaders(&vertShaderId, nullptr, nullptr);
        return PL_ERR_VERT_SHADER_COMPILE;
    }

    std::cout << "loading " << fragShaderFile << std::endl;
    std::string fragShaderSource;
    err = readFile(fragShaderFile, fragShaderSource);
    if (err != 0) {
        CERR(PL_ERR_FILE_NOT_FOUND, err);
        freeShaders(&vertShaderId, nullptr, nullptr);
        return PL_ERR_FILE_NOT_FOUND;
    }

    GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragShaderSourcePtr = fragShaderSource.c_str();
    glShaderSource(fragShaderId, 1, &fragShaderSourcePtr, nullptr);
    glCompileShader(fragShaderId);
    err = checkShader(fragShaderId);
    if (err != 0) {
        CERR(PL_ERR_FRAG_SHADER_COMPILE, err);
        freeShaders(&vertShaderId, &fragShaderId, nullptr);
        return PL_ERR_FRAG_SHADER_COMPILE;
    }

    *programId = glCreateProgram();
    glAttachShader(*programId, vertShaderId);
    glAttachShader(*programId, fragShaderId);
    glLinkProgram(*programId);
    err = checkProgram(*programId);
    if (err != 0) {
        CERR(PL_ERR_LINK_PROGRAM, err);
        freeProgram(programId, &vertShaderId, &fragShaderId);
        return PL_ERR_LINK_PROGRAM;
    }

    freeShaders(&vertShaderId, &fragShaderId, programId);

    return 0;
}
