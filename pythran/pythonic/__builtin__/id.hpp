#ifndef PYTHONIC_BUILTIN_ID_HPP
#define PYTHONIC_BUILTIN_ID_HPP

#include "pythonic/include/__builtin__/id.hpp"

#include "pythonic/utils/functor.hpp"

/*
 * We use uintptr_t conversion because on windows 64 bits, sizeof(void*) == 8
 * and sizeof(long) == 4. Because of this, void* to long is forbidden but
 * void* -> uintptr_t -> long is allowed
 * Accuracy is lost this way...
 */

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    long id(T const &t)
    {
      return t.id();
    }

    long id(long const &t)
    {
      return reinterpret_cast<uintptr_t>(&t);
    }

    long id(double const &t)
    {
      return reinterpret_cast<uintptr_t>(&t);
    }

    long id(bool const &t)
    {
      return reinterpret_cast<uintptr_t>(&t);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, id);
  }
}

#endif
