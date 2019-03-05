#ifndef PYTHONIC_BUILTIN_SORTED_HPP
#define PYTHONIC_BUILTIN_SORTED_HPP

#include "pythonic/include/__builtin__/sorted.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class Iterable>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq)
  {
    types::list<typename std::remove_cv<typename std::iterator_traits<
        typename Iterable::iterator>::value_type>::type> out(seq.begin(),
                                                             seq.end());
    std::sort(out.begin(), out.end());
    return out;
  }
#if defined(PY_MAJOR_VERSION) && PY_MAJOR_VERSION < 3
  template <class Iterable, class C>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq, C const &cmp)
  {
    types::list<typename std::remove_cv<typename std::iterator_traits<
        typename Iterable::iterator>::value_type>::type> out(seq.begin(),
                                                             seq.end());
    std::sort(out.begin(), out.end(), cmp);
    return out;
  }
#else

  template <class Iterable, class Key>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq, Key const &key, bool reverse)
  {
    using value_type = typename std::remove_cv<typename std::iterator_traits<
        typename Iterable::iterator>::value_type>::type;
    types::list<value_type> out(seq.begin(), seq.end());
    if (reverse)
      std::sort(out.begin(), out.end(),
                [&key](value_type const &self, value_type const &other) {
                  return key(self) > key(other);
                });
    else
      std::sort(out.begin(), out.end(),
                [&key](value_type const &self, value_type const &other) {
                  return key(self) < key(other);
                });
    return out;
  }

  template <class Iterable>
  types::list<typename std::remove_cv<typename std::iterator_traits<
      typename Iterable::iterator>::value_type>::type>
  sorted(Iterable const &seq, types::none_type const &key, bool reverse)
  {
    using value_type = typename std::remove_cv<typename std::iterator_traits<
        typename Iterable::iterator>::value_type>::type;
    types::list<value_type> out(seq.begin(), seq.end());
    if (reverse)
      std::sort(out.begin(), out.end(),
                [](value_type const &self, value_type const &other) {
                  return self > other;
                });
    else
      std::sort(out.begin(), out.end());
    return out;
  }
#endif
}
PYTHONIC_NS_END

#endif
