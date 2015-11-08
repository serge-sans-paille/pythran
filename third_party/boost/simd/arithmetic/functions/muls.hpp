//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_MULS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_MULS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  muls generic tag

      Represents the muls function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct muls_ : ext::elementwise_<muls_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<muls_> parent;
    };
  }
  /*!
    Computes the saturated multiplication of the two inputs.

    @par semantic:
    For any given value @c x, @c y of type @c T:

    @code
    T r = muls(x, y);
    @endcode

    The code is similar to:

    @code
    T r = x*y
    @endcode

    @par Alias

    saturated_mul

    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::muls_, muls, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::muls_, saturated_mul, 2)
} }

#endif
