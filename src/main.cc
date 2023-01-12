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
#include "util/delta.hh"

#include "object/walk_camera.hh"
#include "scene/museum.hh"

using namespace pl;
using namespace opl;
using namespace spl;
using namespace upl;

const glm::mat4 I = glm::identity<glm::mat4>();

WalkCamera camera(
    glm::vec3{ 0.0f, 0.0f,  3.0f },
    glm::vec3{ 0.0f, 0.0f, -1.0f },
    glm::vec3{ 0.0f, 1.0f,  0.0f },
    glm::vec3{ 0.0f, 1.0f,  0.0f });

DeltaF dtime;
DeltaF dyaw;
DeltaF dpitch;
bool changingDirection = false;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x;
        double y;
        glfwGetCursorPos(window, &x, &y);
        dyaw.tick((float) x);
        dpitch.tick((float) y);
        changingDirection = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        dyaw.reset();
        dpitch.reset();
        changingDirection = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {
    if (changingDirection) {
        dyaw.tick((float) x);
        dpitch.tick((float) y);
        camera.look(-1 * dyaw.delta(), -1 * dpitch.delta());
    }
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
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
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

    dtime.tick((float) glfwGetTime());

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(window)) {
        dtime.tick((float) glfwGetTime());

        glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world.view = camera.buildView();
        world.projection = camera.buildProjection();

        err = drawMuseum(museum, world);
        if (err != 0) {
            CERR_MSG(PL_ERR_DRAW_SCENE, err, "Museum Scene Error");
            return err;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        else {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.moveFoward(dtime.delta());
            else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.moveFoward(-1 * dtime.delta());

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.moveRight(-1 * dtime.delta());
            else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.moveRight(dtime.delta());

            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
                camera.moveUp(dtime.delta());
            else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
                camera.moveUp(-1 * dtime.delta());
        }
    }

    glfwTerminate();

    return 0;
}
