#ifndef PYTHONIC_BUILTIN_SORTED_HPP
#define PYTHONIC_BUILTIN_SORTED_HPP

#include "pythonic/include/__builtin__/sorted.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>

namespace pythonic
{

  namespace __builtin__
  {

    template <class Iterable>
    types::list<
        typename std::remove_cv<typename Iterable::iterator::value_type>::type>
    sorted(Iterable const &seq)
    {
      types::list<typename std::remove_cv<
          typename Iterable::iterator::value_type>::type> out(seq.begin(),
                                                              seq.end());
      std::sort(out.begin(), out.end());
      return out;
    }
    template <class Iterable, class C>
    types::list<
        typename std::remove_cv<typename Iterable::iterator::value_type>::type>
    sorted(Iterable const &seq, C const &cmp)
    {
      types::list<typename std::remove_cv<
          typename Iterable::iterator::value_type>::type> out(seq.begin(),
                                                              seq.end());
      std::sort(out.begin(), out.end(), cmp);
      return out;
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, sorted);
  }
}

#endif
