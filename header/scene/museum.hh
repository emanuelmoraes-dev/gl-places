#ifndef _PL_MUSEUM_HH_INCLUDED_
#define _PL_MUSEUM_HH_INCLUDED_

#include "object/vao.hh"
#include "object/directional_light.hh"
#include "app.hh"
#include "world.hh"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct MuseumWalls {
    GLuint programId;
    GLuint textureId;
    Vao vao;
};

class Museum {
public:
    MuseumWalls walls;
    DirectionalLight light;

    ~Museum();
};

int museumLoad(Museum& museum, App const& app);
int museumDraw(Museum const& museum, World const& world);

#endif
