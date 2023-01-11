#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "errors.hh"
#include "env.hh"
#include "app.hh"

#include "util/fs.hh"
#include "util/gl_info.hh"

#include "object/walk_camera.hh"
#include "scene/museum.hh"

const glm::mat4 I = glm::identity<glm::mat4>();

WalkCamera camera(
    glm::vec3{ 0.0f, 0.0f,  3.0f },
    glm::vec3{ 0.0f, 0.0f, -1.0f },
    glm::vec3{ 0.0f, 1.0f,  0.0f },
    glm::vec3{ 0.0f, 1.0f,  0.0f });

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void resized(GLFWwindow* window, int width, int height) {
    camera._aspect = (float) width / height;
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

    GLFWwindow* window = glfwCreateWindow(PL_ENV_WINDOW_WIDTH, PL_ENV_WINDOW_HEIGHT, PL_ENV_WINDOW_TITLE, nullptr, nullptr);
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

    resized(window, PL_ENV_WINDOW_WIDTH, PL_ENV_WINDOW_HEIGHT);

    World world(I);

    Museum museum;
    err = loadMuseum(museum, app);
    if (err != 0) {
        CERR_MSG(PL_ERR_LOAD_SCENE, err, "Museum Scene Error");
        return err;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        world.view = camera.buildView();
        world.projection = camera.buildProjection();

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
