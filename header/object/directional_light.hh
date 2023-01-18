#ifndef _PL_OBJECT_DIRECTIONAL_LIGHT_HH_INCLUDED_
#define _PL_OBJECT_DIRECTIONAL_LIGHT_HH_INCLUDED_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace opl {
    struct DirectionalLight {
        glm::vec3 direction;
        float intensity;
    };
}

#endif
