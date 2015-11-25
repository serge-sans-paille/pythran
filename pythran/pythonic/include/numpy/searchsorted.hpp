#ifndef PYTHONIC_INCLUDE_NUMPY_SEARCHSORTED_HPP
#define PYTHONIC_INCLUDE_NUMPY_SEARCHSORTED_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/__builtin__/None.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"
#include "pythonic/include/numpy/asarray.hpp"

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {

    template <class T, class U>
    typename std::enable_if<!types::is_numexpr_arg<T>::value, long>::type
    searchsorted(U const &a, T const &v, types::str const &side = "left");

    template <class E, class I0, class I1>
    void _search_sorted(E const &a, I0 ibegin, I0 iend, I1 obegin,
                        types::str const &side, utils::int_<1>);

    template <class E, class I0, class I1, size_t N>
    void _search_sorted(E const &a, I0 ibegin, I0 iend, I1 obegin,
                        types::str const &side, utils::int_<N>);

    template <class E, class T>
    typename std::enable_if<types::is_numexpr_arg<E>::value,
                            types::ndarray<long, E::value>>::type
    searchsorted(T const &a, E const &v, types::str const &side = "left");

    DECLARE_FUNCTOR(pythonic::numpy, searchsorted);
  }
}

#endif
