#include "object/walk_camera.hh"
#include "config.hh"
#include "env.hh"

using namespace opl;

const glm::mat4 I = glm::identity<glm::mat4>();

opl::WalkCamera::WalkCamera(glm::vec3 eye, glm::vec3 direction, glm::vec3 up, glm::vec3 surfaceNormal) :
    _eye(eye),
    _direction(glm::normalize(direction)),
    _up(glm::normalize(up)),
    _surfaceNormal(glm::normalize(surfaceNormal)),

    _fov(glm::radians(PL_WALK_CAMERA_PERSPECTIVE_FOV)),
    _aspect((float) PL_ENV_WINDOW_WIDTH / PL_ENV_WINDOW_HEIGHT),
    _near(PL_WALK_CAMERA_PERSPECTIVE_NEAR),
    _far(PL_WALK_CAMERA_PERSPECTIVE_FAR),

    _speed(PL_WALK_CAMERA_SPEED),
    _sensitivity(PL_WALK_CAMERA_SENSITIVITY) {}

glm::mat4 opl::WalkCamera::buildView() const {
    return glm::lookAt(_eye, _eye + _direction, _up);
}

glm::mat4 opl::WalkCamera::buildProjection() const {
    return glm::perspective(_fov, _aspect, _near, _far);
}

void opl::WalkCamera::moveFoward(float amount) {
    // axes
    const glm::vec3 direction = glm::normalize(_direction);
    const glm::vec3 up = glm::normalize(_up);
    const glm::vec3 right = glm::normalize(glm::cross(direction, up));
    const glm::vec3 surfaceNormal = glm::normalize(_surfaceNormal);
    const glm::vec3 surfaceDirection = glm::normalize(glm::cross(right, surfaceNormal));

    _eye += surfaceDirection * amount * _speed;
}

void opl::WalkCamera::moveRight(float amount) {
    const glm::vec3 right = glm::normalize(glm::cross(_direction, _up));
    _eye += right * amount * _speed * (-1.0f);
}

void opl::WalkCamera::moveUp(float amount) {
    const glm::vec3 surfaceNormal = glm::normalize(_surfaceNormal);
    _eye += surfaceNormal * amount * _speed * (-1.0f);
}

void opl::WalkCamera::look(float yaw, float pitch) {
    // axes
    const glm::vec3 direction = glm::normalize(_direction);
    const glm::vec3 up = glm::normalize(_up);
    const glm::vec3 right = glm::normalize(glm::cross(direction, up));
    const glm::vec3 surfaceNormal = glm::normalize(_surfaceNormal);

    // rotate matrixes
    const glm::mat4 yawRotate = glm::rotate(I, glm::radians(yaw * _sensitivity), surfaceNormal);
    const glm::mat4 pitchRotate = glm::rotate(I, glm::radians(pitch * _sensitivity), right);

    // update
    _up = glm::normalize(pitchRotate * glm::vec4 { up, 0.0f });
    _direction = glm::normalize(yawRotate * pitchRotate * glm::vec4 { direction, 0.0f });
}
