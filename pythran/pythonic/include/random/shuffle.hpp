#ifndef PYTHONIC_INCLUDE_RANDOM_SHUFFLE_HPP
#define PYTHONIC_INCLUDE_RANDOM_SHUFFLE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/random/random.hpp"

namespace pythonic
{

  namespace random
  {
    template <class T>
    void shuffle(T &seq);
    template <class T, class function>
    void shuffle(T &seq, function &&randf);

    DECLARE_FUNCTOR(pythonic::random, shuffle)
  }
}

#endif
