//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ONEOSQRT5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ONEOSQRT5_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate  \f$1/\sqrt5\f$

    @par Semantic:

    @code
    T r = Oneosqrt5<T>();
    @endcode

    is similar to:

    @code
      r =  1/sqrt(T(5));
    @endcode

    @return The Oneosqrt5 constant for the proper type
  **/
  template<typename T> T Oneosqrt5();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant oneosqrt5.

      @return The Oneosqrt5 constant for the proper type
    **/
    const boost::dispatch::functor<tag::oneosqrt5_> oneosqrt5 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/oneosqrt5.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
