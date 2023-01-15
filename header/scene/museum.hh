#ifndef _PL_MUSEUM_HH_INCLUDED_
#define _PL_MUSEUM_HH_INCLUDED_

#include "app.hh"
#include "world.hh"
#include "object/vao.hh"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace spl {
    struct MuseumWalls {
        GLuint programId;
        GLuint textureId;

        opl::Vao object;
        glm::mat4 objectModel;

        opl::Vao border;
        glm::mat4 insideBorderModel;
        glm::mat4 outsideBorderModel;

        MuseumWalls();
        ~MuseumWalls();
    };

    struct Museum {
        MuseumWalls walls;
    };

    int loadMuseum(Museum& museum, pl::App const& app);
    int drawMuseum(Museum const& museum, pl::World const& world);
}

#endif
