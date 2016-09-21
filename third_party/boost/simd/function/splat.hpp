//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SPLAT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    Splat

    Fills an entire SIMD vector with its argument.

    @par Semantic

    For any type @c T and value @c x of type @c U:

    @code
    T r = splat(x);
    @endcode

    is similar to:

    @code
    for(int i=0;i<T::static_size;++i) r[i] = x;
    @endcode

  **/
  template<typename T, typename U> T splat(U const& x) {}
} }
#endif

#include <boost/simd/function/scalar/splat.hpp>
#include <boost/simd/function/simd/splat.hpp>

#endif
