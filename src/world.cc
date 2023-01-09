#include "world.hh"

const glm::mat4 I = glm::identity<glm::mat4>();

World::World() :
    model(I),
    view(I),
    projection(I) {}
