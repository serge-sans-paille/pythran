//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SHR_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SHR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  shr generic tag

      Represents the shr function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct shr_ : ext::elementwise_<shr_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<shr_> parent;
    };
  }
  /*!
    Returns the first entry logically shifted right
    by value of the second entry. If the second entry is negative
    the result is not defined.

    @par semantic:
    For any given value @c x of type @c T, n  of type @c I:

    @code
    T r = shr(x, n);
    @endcode

    @par Alias:

    @c shri

    @see  @funcref{shift_right}, @funcref{shift_left}, @funcref{rshl}, @funcref{rshr}, @funcref{rol}, @funcref{ror}
    @param  a0
    @param  a1

    @return      a value of the same type as the first input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shr_, shr, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::shr_, shri, 2)
} }

#endif
