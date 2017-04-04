//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRTVALMAX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRTVALMAX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the square root of the greatest finite representable value


    @par Header <boost/simd/constant/sqrtvalmax.hpp>

    @par Semantic:

    @code
    T r = Sqrtvalmax<T>();
    @endcode

    is similar to:

    @code
    T r =  sqrt(Valmax<T>();
    @endcode

    @return The Sqrtvalmax constant for the proper type
  **/
  template<typename T> T Sqrtvalmax();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant sqrtvalmax.

      @return The Sqrtvalmax constant for the proper type
    **/
    Value Sqrtvalmax();
  }
} }
#endif

#include <boost/simd/constant/scalar/sqrtvalmax.hpp>
#include <boost/simd/constant/simd/sqrtvalmax.hpp>

#endif
