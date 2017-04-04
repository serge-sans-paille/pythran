//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value \f$\pi\f$ that is the half length of a circle of radius one
    ... in normal temperature and pressure conditions.


    @par Header <boost/simd/constant/pi.hpp>

    @par Semantic:

    @code
    T r = Pi<T>();
    @endcode

    is similar to:

    @code
    T r = T(4*atan(1));
    @endcode

    @return The Pi constant for the proper type
  **/
  template<typename T> T Pi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant pi.

      @return The Pi constant for the proper type
    **/
    Value Pi();
  }
} }
#endif

#include <boost/simd/constant/scalar/pi.hpp>
#include <boost/simd/constant/simd/pi.hpp>

#endif
