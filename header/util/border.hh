#ifndef _PL_UTIL_BORDER_HH_INCLUDED_
#define _PL_UTIL_BORDER_HH_INCLUDED_

#include <vector>
#include <GL/glew.h>

#define UPL_JOIN_BORDERS(targetElements, pn, borderElements1, borderElements2) \
upl::joinBorders(targetElements, (GLsizei) pn, (GLsizei) borderElements1.size(), borderElements1.data(), borderElements2.data())

namespace upl {
    void joinBorders(std::vector<GLuint>& targetElements, GLsizei pn, GLsizei en, const GLuint* borderElements1, const GLuint* borderElements2);
}

#endif
