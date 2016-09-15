//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ENUMERATE_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-swar

    Linear enumeration of value

    Return a SIMD register containing a linear enumeration of values defined
    by a @c seed value and a @c step value.

    @par Semantic:

    For any given SIMD type @c T, the following code:

    @code
    T r = enumerate<T>();
    @endcode

    is equivalent to

    @code
    T r = make<T>(0, 1, ... , N-1);
    @endcode

    where @c N is the equal to <tt>cardinal_of<T>::value</tt>.

    For any given SIMD type @c T, and any value @c seed of a scalar type @c S, the following code:

    @code
    T r = enumerate<T>(seed);
    @endcode

    is equivalent to

    @code
    T r = make<T>(seed, seed + 1, ... ,  seed + (N-1));
    @endcode

    where @c N is the equal to <tt>cardinal_of<T>::value</tt>.

    For any given SIMD type @c T, and any value @c seed and @c step of a SIMD type @c S, the
    following code:

    @code
    T r = enumerate<T>(seed, step);
    @endcode

    is equivalent to

    @code
    T r = seed + step*enumerate<T>();
    @endcode

    @param seed Initial value of the enumeration. By default, equals to 0.
    @param step Initial value of the enumeration. By default, equals to 1.

    @return A pack containing the enumeration based on @c seed and @c step
  **/
  template<class T, class B, class S>
  T enumerate(const B& seed = 0, const S& step = 1) noexcept;

#endif
} }

#include <boost/simd/function/scalar/enumerate.hpp>
#include <boost/simd/function/simd/enumerate.hpp>

#endif
