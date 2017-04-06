//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_NAN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_NAN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the Not a Number (Nan) constant.


    @par Header <boost/simd/constant/nan.hpp>

    @par Semantic

    For any type @c T,

    @code
    T x = Nan<T>();
    @endcode

    return the Nan representation for this type, i.e QuietNan for IEEE reals and
    0 for integers.

    @return The Nan constant for the proper type
  **/
  template<typename T> T Nan();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the Not a Number (Nan) constant.

      @par Semantic

      For any type @c T,

      @code
      T x = nan(as(T{}));
      @endcode

      return the Nan representation for this type, i.e QuietNan for IEEE reals and
      0 for integers.

      @return The Nan constant for the proper type
    **/
    Value Nan();
  }
} }
#endif

#include <boost/simd/constant/scalar/nan.hpp>
#include <boost/simd/constant/simd/nan.hpp>

#endif
