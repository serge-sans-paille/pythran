//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOTO31_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOTO31_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate  2 to the power 31 (\f$2^{31}\f$)

    @par Semantic:

    @code
    T r = Twoto31<T>();
    @endcode

    is similar to:

    @code
    T r = pow(2, 31);
    @endcode

    @return The Twoto31 constant for the proper type
  **/
  template<typename T> T Twoto31();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant twoto31.

      @return The Twoto31 constant for the proper type
    **/
    const boost::dispatch::functor<tag::twoto31_> twoto31 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/twoto31.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
