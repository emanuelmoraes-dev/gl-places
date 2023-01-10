#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "app.hh"
#include "errors.hh"

#include "util/fs.hh"
#include "util/gl_info.hh"

#include "scene/museum.hh"

#define PL_WINDOW_WIDTH 800
#define PL_WINDOW_HEIGHT 600

const glm::mat4 I = glm::identity<glm::mat4>();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void resized(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

int main(int argc, const char* argv[]) {
    const App app(argc, argv);

    int err = 0;

    err = glfwInit();
    if (err != GLFW_TRUE) {
        CERR(PL_ERR_GLFW_INIT, err);
        return PL_ERR_GLFW_INIT;
    }

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(PL_WINDOW_WIDTH, PL_WINDOW_HEIGHT, "GL Places", nullptr, nullptr);
    if (window == nullptr) {
        CERR(PL_ERR_WINDOW, err);
        return PL_ERR_WINDOW;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, resized);

    err = glewInit();
    if (err != GLEW_OK) {
        CERR(PL_ERR_GLEW_INIT, err);
        return PL_ERR_GLEW_INIT;
    }

    err = coutAllInfo();
    if (err != 0) {
        return err;
    }

    resized(window, PL_WINDOW_WIDTH, PL_WINDOW_HEIGHT);

    const glm::mat4 world = I;

    Museum museum;
    err = loadMuseum(museum, app);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SCENE, err, "Museum Scene Error");
        return err;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        err = drawMuseum(museum, world);
        if (err != 0) {
            CERR_MSG(PL_ERR_DRAW_SCENE, err, "Museum Scene Error");
            return err;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
