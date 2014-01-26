#ifndef PYTHONIC_UTILS_WRAP_HPP
#define PYTHONIC_UTILS_WRAP_HPP

//Use when the C/C++ function do not have the same name
//than in python
#define WRAP(type,name,cname,argType)\
    type name(argType x){ return cname(x); }

#endif
