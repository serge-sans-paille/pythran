//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRT_2O_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRT_2O_2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value \f$\frac{\sqrt2}2\f$

    @par Semantic:

    @code
    T r = Sqrt_2o_2<T>();
    @endcode

    is similar to:

    @code
    T r = T(sqrt(T(2)))/T(2);
    @endcode

    @return The Sqrt_2o_2 constant for the proper type
  **/
  template<typename T> T Sqrt_2o_2();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant sqrt_2o_2.

      @return The Sqrt_2o_2 constant for the proper type
    **/
    const boost::dispatch::functor<tag::sqrt_2o_2_> sqrt_2o_2 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/sqrt_2o_2.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
