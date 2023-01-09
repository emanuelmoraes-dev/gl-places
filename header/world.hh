#ifndef _PL_WORLD_HH_INCLUDED_
#define _PL_WORLD_HH_INCLUDED_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class World {
public:
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    World();
};

#endif
