#ifndef PYTHONIC_INCLUDE_RANDOM_SHUFFLE_HPP
#define PYTHONIC_INCLUDE_RANDOM_SHUFFLE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/random.hpp"

namespace pythonic
{

  namespace random
  {
    template <class T>
    void shuffle(T &seq);
    template <class T, class function>
    void shuffle(T &seq, function &&randf);

    PROXY_DECL(pythonic::random, shuffle)
  }
}

#endif
