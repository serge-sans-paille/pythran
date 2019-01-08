#ifndef PYTHONIC_BUILTIN_LEN_HPP
#define PYTHONIC_BUILTIN_LEN_HPP

#include "pythonic/include/__builtin__/len.hpp"

#include "pythonic/types/traits.hpp"
#include "pythonic/utils/functor.hpp"

#include <tuple>
#include <iterator>

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  template <class... Types>
  long len(std::tuple<Types...> const &)
  {
    return sizeof...(Types);
  }

  template <class T>
  typename std::enable_if<types::has_size<T>::value, long>::type len(T const &t)
  {
    return t.size();
  }

  template <class T>
  typename std::enable_if<!types::has_size<T>::value, long>::type
  len(T const &t)
  {
    static_assert(std::is_same<typename std::iterator_traits<
                                   typename T::iterator>::iterator_category,
                               std::random_access_iterator_tag>::value,
                  "distance is ! really efficient without random iterators...");
    return std::distance(std::begin(t), std::end(t));
  }
}
PYTHONIC_NS_END
#endif
