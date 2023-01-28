#ifndef _PL_SCENE_MUSEUM_HH_INCLUDED_
#define _PL_SCENE_MUSEUM_HH_INCLUDED_

#include "app.hh"
#include "world.hh"
#include "object/vao.hh"

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace spl {
    struct MuseumRoomData {
        std::vector<std::string> imgs;
    };

    struct MuseumRooms {
        MuseumRoomData main;
    };

    struct MuseumContent {
        MuseumRooms rooms;
    };

    struct MuseumWalls {
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
        MuseumContent content;
    };

    int loadMuseum(Museum& museum, pl::App const& app);
    int drawMuseum(Museum const& museum, pl::App const& app, pl::World const& world);
}

#endif
