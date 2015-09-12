#ifndef PYTHONIC_INCLUDE_RANDOM_SAMPLE_HPP
#define PYTHONIC_INCLUDE_RANDOM_SAMPLE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/random/random.hpp"

#include "pythonic/include/types/list.hpp"

namespace pythonic
{

  namespace random
  {
    template <class Iterable>
    types::list<typename std::remove_cv<typename std::remove_reference<
        Iterable>::type>::type::iterator::value_type>
    sample(Iterable &&s, size_t k);

    PROXY_DECL(pythonic::random, sample);
  }
}

#endif
