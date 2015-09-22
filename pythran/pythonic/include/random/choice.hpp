#ifndef PYTHONIC_INCLUDE_RANDOM_CHOICE_HPP
#define PYTHONIC_INCLUDE_RANDOM_CHOICE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/random/random.hpp"

namespace pythonic
{

  namespace random
  {

    template <class Seq>
    typename Seq::value_type choice(Seq const &seq);

    PROXY_DECL(pythonic::random, choice);
  }
}

#endif
