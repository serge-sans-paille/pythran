//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_REVERSEBITS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_REVERSEBITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  reversebits generic tag

      Represents the reversebits function in generic contexts.

      @par Models:
      Hieerarchy
    **/
    struct reversebits_ : ext::elementwise_<reversebits_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<reversebits_> parent;
    };
  }
  /*!
    Returns the bits of the entry in reverse order.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = reversebits(x);
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::reversebits_, reversebits, 1)
} }
#endif
