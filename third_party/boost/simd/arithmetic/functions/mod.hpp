//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_MOD_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_MOD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  mod generic tag

      Represents the mod function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct mod_ : ext::elementwise_<mod_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<mod_> parent;
    };
  }
  /*!
    Computes the remainder of division.
    The return value is a0-n*a1, where n is the value a0/a1,
    truncated to -inf.

    @par semantic:
    For any given value @c x, @c y of type @c T:

    @code
    T r = mod(x, y);
    @endcode

    The code is similar to:

    @code
    T r = x-divfloor(x, y)*y;
    @endcode

    @see @funcref{remainder}, @funcref{rem}
    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mod_, mod, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mod_, remfloor, 2)
} }

#endif


