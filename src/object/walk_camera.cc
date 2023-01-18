#include "object/walk_camera.hh"
#include "config.hh"
#include "env.hh"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace opl;

const glm::mat4 I = glm::identity<glm::mat4>();

opl::WalkCamera::WalkCamera(glm::vec3 eye, glm::vec3 direction, glm::vec3 surfaceNormal) :
    _eye(eye),
    _direction(glm::normalize(direction)),
    _surfaceNormal(glm::normalize(surfaceNormal)),

    _fov(glm::radians(PL_WALK_CAMERA_PERSPECTIVE_FOV)),
    _viewPortWidth(PL_ENV_WINDOW_WIDTH),
    _viewPortHeight(PL_ENV_WINDOW_HEIGHT),
    _near(PL_WALK_CAMERA_PERSPECTIVE_NEAR),
    _far(PL_WALK_CAMERA_PERSPECTIVE_FAR),

    _speed(PL_WALK_CAMERA_SPEED),
    _sensitivity(PL_WALK_CAMERA_SENSITIVITY) {}

glm::mat4 opl::WalkCamera::buildView() const {
    return glm::lookAt(_eye, _eye + _direction, _surfaceNormal);
}

glm::mat4 opl::WalkCamera::buildProjection() const {
    const float aspect = (float) _viewPortWidth / _viewPortHeight;
    return glm::perspective(_fov, aspect, _near, _far);
}

void opl::WalkCamera::moveFoward(float amount) {
    // axes
    const glm::vec3 direction = glm::normalize(_direction);
    const glm::vec3 surfaceNormal = glm::normalize(_surfaceNormal);
    const glm::vec3 right = glm::normalize(glm::cross(direction, surfaceNormal));
    const glm::vec3 surfaceDirection = glm::normalize(glm::cross(surfaceNormal, right));

    _eye += surfaceDirection * amount * _speed;
}

void opl::WalkCamera::moveRight(float amount) {
    const glm::vec3 right = glm::normalize(glm::cross(_direction, _surfaceNormal));
    _eye += right * amount * _speed;
}

void opl::WalkCamera::moveUp(float amount) {
    const glm::vec3 surfaceNormal = glm::normalize(_surfaceNormal);
    _eye += surfaceNormal * amount * _speed;
}

void opl::WalkCamera::look(float yaw, float pitch) {
    // axes
    const glm::vec3 direction = glm::normalize(_direction);
    const glm::vec3 surfaceNormal = glm::normalize(_surfaceNormal);
    const glm::vec3 right = glm::normalize(glm::cross(direction, surfaceNormal));

    // rotate matrixes
    const glm::mat4 yawRotate = glm::rotate(I, glm::radians(yaw * _sensitivity), surfaceNormal);
    const float minPitchAngle = glm::radians(5.0f);
    const glm::mat4 newPitchRotate = glm::rotate(I, glm::radians(pitch * _sensitivity), right);
    const glm::vec3 newPitchDirection = newPitchRotate * glm::vec4 { direction, 0.0f };
    const glm::mat4 pitchRotate = glm::angle(newPitchDirection, surfaceNormal) > minPitchAngle
        && glm::angle(newPitchDirection, -surfaceNormal) > minPitchAngle
        ? newPitchRotate
        : I;

    // update
    _direction = glm::normalize(yawRotate * pitchRotate * glm::vec4 { direction, 0.0f });
}
