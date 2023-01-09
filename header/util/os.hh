#ifndef _GL_PLACES_OS_HH_INCLUDED_
#define _GL_PLACES_OS_HH_INCLUDED_

#if defined(_WIN32) || defined(WIN32)
    #define PL_SLASH "\\"
#else
    #define PL_SLASH "/"
#endif

#endif
