#ifndef _PL_WALK_CAMERA_HH_INCLUDED_
#define _PL_WALK_CAMERA_HH_INCLUDED_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace opl {
    class WalkCamera {
    public:
        glm::vec3 _eye;
        glm::vec3 _direction;
        glm::vec3 _surfaceNormal;

        float _fov;
        float _aspect;
        float _near;
        float _far;

        float _speed;
        float _sensitivity;

        WalkCamera(glm::vec3 eye, glm::vec3 direction, glm::vec3 surfaceNormal);

        glm::mat4 buildView() const;
        glm::mat4 buildProjection() const;

        void moveFoward(float amount);
        void moveRight(float amount);
        void moveUp(float amount);
        void look(float yaw, float pitch);
    };
}

#endif
