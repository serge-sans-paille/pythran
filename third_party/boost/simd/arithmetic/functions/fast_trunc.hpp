//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_TRUNC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_TRUNC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  fast_trunc generic tag

      Represents the fast_trunc function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fast_trunc_ : ext::elementwise_<fast_trunc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_trunc_> parent;
    };
  }
  /*!
    Computes the truncation toward zero of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = fast_trunc(x);
    @endcode

    The code is similar to:

    @code
    T r = tofloat(toint(x)));
    @endcode

    fast means that no provisions are taken for floating to large to fit
    in the same size integer type.

    @see @funcref{trunc}
    @par Alias

    fast_fix

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_trunc_, fast_trunc, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_trunc_, fast_fix, 1)
} }

#endif
