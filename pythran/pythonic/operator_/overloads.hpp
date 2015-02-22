#ifndef PYTHONIC_OPERATOR_OVERLOADS_HPP
#define PYTHONIC_OPERATOR_OVERLOADS_HPP

#define PYTHONIC_OPERATOR_OVERLOAD(type, opname, op) type opname(type a, type b) { return a op b; }

// workaround the fact that char and short computations are done using int in C, while they are done at their respective type in numpy
#define DEFINE_ALL_OPERATOR_OVERLOADS(opname, op) \
  PYTHONIC_OPERATOR_OVERLOAD(unsigned char, opname, op)\
  PYTHONIC_OPERATOR_OVERLOAD(signed char, opname, op)\
  PYTHONIC_OPERATOR_OVERLOAD(unsigned short, opname, op)\
  PYTHONIC_OPERATOR_OVERLOAD(signed short, opname, op)\

#endif
