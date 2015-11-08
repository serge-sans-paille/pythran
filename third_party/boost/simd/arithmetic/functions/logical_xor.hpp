//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_LOGICAL_XOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  logical_xor generic tag

      Represents the logical_xor function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct logical_xor_ : ext::elementwise_<logical_xor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<logical_xor_> parent;
    };
  }
  /*!
    Computes the logical xor of its parameter.

    @par semantic:
    For any given value @c x and @c y of type @c T:

    @code
    as_logical<T> r = logical_xor(x, y);
    @endcode

    is similar to:

    @code
    as_logical<T> r = !x != !y;
    @endcode

    @param  a0
    @param  a1

    @return a logical value of the logical type associated to the input.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_xor_, logical_xor, 2)
} }

#endif


