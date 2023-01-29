#ifndef _PL_UTIL_COND_HH_INCLUDED_
#define _PL_UTIL_COND_HH_INCLUDED_

#define UPL_COND(expression, ifTrue, ifFalse) (\
(expression) ? (ifTrue) : (ifFalse)\
)

#define UPL_NULLABLE(pointer, expression) \
UPL_COND(pointer != nullptr, expression, nullptr)

#endif
