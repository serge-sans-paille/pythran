//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant \f$2\pi\f$.

    @par Semantic:

    For type T:

    @code
    T r = Twopi<T>();
    @endcode

    is similar to:

    @code
    T r = Two<T>()*Pi<T>();
    @endcode

    @return a value of type T

**/
  template<typename T> T Twopi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant \f$\frac2\pi\f$.

      Generate the  constant twopi.

      @return The Twopi constant for the proper type
    **/
    Value Twopi();
  }
} }
#endif

#include <boost/simd/constant/definition/twopi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
