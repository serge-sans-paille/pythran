#ifndef PYTHONIC_INCLUDE_BUILTIN_SORTED_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SORTED_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  template <class Iterable>
  types::list<std::remove_cv_t<typename std::iterator_traits<typename std::decay_t<Iterable>::iterator>::value_type>>
  sorted(Iterable &&seq);

  template <class Iterable, class Key>
  types::list<std::remove_cv_t<typename std::iterator_traits<typename std::decay_t<Iterable>::iterator>::value_type>>
  sorted(Iterable &&seq, Key const &key, bool reverse = false);

  template <class Iterable>
  types::list<std::remove_cv_t<typename std::iterator_traits<typename std::decay_t<Iterable>::iterator>::value_type>>
  sorted(Iterable &&seq, types::none_type const &key, bool reverse = false);

  DEFINE_FUNCTOR(pythonic::builtins, sorted);
} // namespace builtins
PYTHONIC_NS_END

#endif
