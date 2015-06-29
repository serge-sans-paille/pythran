#ifndef PYTHONIC_BUILTIN_SORTED_HPP
#define PYTHONIC_BUILTIN_SORTED_HPP

#include "pythonic/include/builtins/sorted.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

#include <algorithm>

namespace pythonic
{

  namespace builtins
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

    PROXY_IMPL(pythonic::builtins, sorted);
  }
}

#endif
