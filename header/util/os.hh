#ifndef _PL_UTIL_OS_HH_INCLUDED_
#define _PL_UTIL_OS_HH_INCLUDED_

#if defined(_WIN32) || defined(WIN32)
    #define PL_SLASH "\\"
#else
    #define PL_SLASH "/"
#endif

#endif
