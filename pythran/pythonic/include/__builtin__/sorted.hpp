#ifndef PYTHONIC_INCLUDE_BUILTIN_SORTED_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SORTED_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class Iterable>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq);

#if defined(PY_MAJOR_VERSION) && PY_MAJOR_VERSION < 3
  template <class Iterable, class C>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq, C const &cmp);
#else

  template <class Iterable, class Key>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq, Key const &key, bool reverse = false);

  template <class Iterable>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq, types::none_type const &key,
         bool reverse = false);
#endif

  DEFINE_FUNCTOR(pythonic::__builtin__, sorted);
}
PYTHONIC_NS_END

#endif
