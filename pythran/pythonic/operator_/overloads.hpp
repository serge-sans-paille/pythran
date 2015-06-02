#ifndef PYTHONIC_OPERATOR_OVERLOADS_HPP
#define PYTHONIC_OPERATOR_OVERLOADS_HPP

#include "pythonic/include/operator_/overloads.hpp"

#define PYTHONIC_OPERATOR_OVERLOAD_IMPL(type, opname, op)                      \
  type opname(type a, type b)                                                  \
  {                                                                            \
    return a op b;                                                             \
  }

// workaround the fact that char and short computations are done using int in C,
// while they are done at their respective type in numpy
#define DEFINE_ALL_OPERATOR_OVERLOADS_IMPL(opname, op)                         \
  PYTHONIC_OPERATOR_OVERLOAD_IMPL(unsigned char, opname, op)                   \
  PYTHONIC_OPERATOR_OVERLOAD_IMPL(signed char, opname, op)                     \
  PYTHONIC_OPERATOR_OVERLOAD_IMPL(unsigned short, opname, op)                  \
  PYTHONIC_OPERATOR_OVERLOAD_IMPL(signed short, opname, op)

#endif
