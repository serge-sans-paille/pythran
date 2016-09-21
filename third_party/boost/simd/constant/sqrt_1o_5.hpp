//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRT_1O_5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRT_1O_5_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value \f$ \sqrt{\frac15}\f$

    @par Semantic:

    @code
    T r = Sqrt_1o_5<T>();
    @endcode

    is similar to:

    @code
    T r = sqrt(T(1)/T(5));
    @endcode


    @return The Sqrt_1o_5 constant for the proper type
  **/
  template<typename T> T Sqrt_1o_5();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant sqrt_1o_5.

      @return The Sqrt_1o_5 constant for the proper type
    **/
    const boost::dispatch::functor<tag::sqrt_1o_5_> sqrt_1o_5 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/sqrt_1o_5.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
