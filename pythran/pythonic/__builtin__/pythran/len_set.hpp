#ifndef PYTHONIC_BUILTIN_PYTHRAN_LEN_SET_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_LEN_SET_HPP

#include "pythonic/include/__builtin__/pythran/len_set.hpp"

#include "pythonic/utils/functor.hpp"

#include <set>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {

    template <class Iterable>
    long len_set(Iterable const &s)
    {
      return std::set<typename std::iterator_traits<
          typename Iterable::iterator>::value_type>(s.begin(), s.end()).size();
    }
  }
}
PYTHONIC_NS_END

#endif
