#ifndef _PL_MUSEUM_HH_INCLUDED_
#define _PL_MUSEUM_HH_INCLUDED_

#include "app.hh"
#include "world.hh"
#include "object/vao.hh"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct MuseumWalls {
    GLuint programId;
    GLuint textureId;
    Vao vao;
    glm::mat4 model;

    MuseumWalls();
    ~MuseumWalls();
};

struct Museum {
    MuseumWalls walls;
};

int loadMuseum(Museum& museum, App const& app);
int drawMuseum(Museum const& museum, World const& world);

#endif
