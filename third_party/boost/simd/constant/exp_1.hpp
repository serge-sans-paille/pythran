//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_EXP_1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_EXP_1_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant e.

    @par Semantic:
    The e constant is the real number such that \f$\log(e) = 1\f$

    @code
    T r = Exp_1<T>();
    @endcode

    is similar to:

    @code
      r =  T(2.71828182845904523536028747135266249775724709369995);
    @endcode


**/
  template<typename T> T Exp_1();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant e.

      Generate the  constant exp_1.

      @return The Exp_1 constant for the proper type
    **/
    const boost::dispatch::functor<tag::exp_1_> exp_1 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/exp_1.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
