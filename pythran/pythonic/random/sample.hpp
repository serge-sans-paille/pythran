#ifndef PYTHONIC_RANDOM_SAMPLE_HPP
#define PYTHONIC_RANDOM_SAMPLE_HPP

#include "pythonic/include/random/sample.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/random/random.hpp"

#include "pythonic/types/list.hpp"

namespace pythonic
{

  namespace random
  {
    template <class Iterable>
    types::list<typename std::remove_cv<typename std::remove_reference<
        Iterable>::type>::type::iterator::value_type>
    sample(Iterable &&s, size_t k)
    {
      using value_type = typename std::remove_cv<typename std::remove_reference<
          Iterable>::type>::type::iterator::value_type;
      types::list<value_type> tmp(s);
      std::vector<size_t> indices(tmp.size());
      std::iota(indices.begin(), indices.end(), 0);
      std::random_shuffle(indices.begin(), indices.end());
      types::list<value_type> out(k);
      for (size_t i = 0; i < k; i++)
        out[i] = tmp[indices[i]];
      return out;
    }

    DEFINE_FUNCTOR(pythonic::random, sample);
  }
}

#endif
