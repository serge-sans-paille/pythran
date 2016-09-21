//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVEXP_1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVEXP_1_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant 1/e.

    @par Semantic:
    The e constant is the real number such that \f$\log(e) = 1\f$.

    @code
    T r = Invexp_1<T>();
    @endcode

    is similar to:

    @code
    r =  T(0.3678794411714423215955237701614608674458111310317678);
    @endcode


**/
  template<typename T> T Invexp_1();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant 1/e.

      Generate the  constant invexp_1.

      @return The Invexp_1 constant for the proper type
    **/
    Value Invexp_1<Value>();
  }
} }
#endif

#include <boost/simd/constant/definition/invexp_1.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
