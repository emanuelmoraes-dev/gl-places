#include "util/border.hh"

#include <unordered_map>

using namespace upl;
using namespace std;

void upl::joinBorders(vector<GLuint>& targetElements, GLsizei pn, GLsizei en, const GLuint* borderElements1, const GLuint* borderElements2) {
    unordered_map<GLuint, GLuint> map;

    for (GLsizei e = 0; e < en; e++) {
        const GLuint element1 = borderElements1[e];
        const GLuint element2 = borderElements2[e] + pn;
        map[element1] = element2;
    }

    for (auto it = map.begin(); it != map.end(); ++it) {
        targetElements.push_back(it->first);
        targetElements.push_back(it->second);
    }
}
