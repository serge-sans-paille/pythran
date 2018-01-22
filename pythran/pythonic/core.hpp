#ifndef PYTHONIC_CORE_HPP
#define PYTHONIC_CORE_HPP

#define PYTHONIC_NS_BEGIN                                                      \
  namespace                                                                    \
  {                                                                            \
    namespace pythonic                                                         \
    {
#define PYTHONIC_NS_END                                                        \
  }                                                                            \
  }

#define STR_(M) #M
// clang-format off
#define INCLUDE_FILE(U, M) STR_(U/M.hpp)
// clang-format on

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/combined.hpp"

#include "pythonic/types/int.hpp"
#include "pythonic/types/float.hpp"

#endif
