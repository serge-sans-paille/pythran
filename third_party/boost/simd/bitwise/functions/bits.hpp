//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_BITS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_BITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  bits generic tag

      Represents the bits function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct bits_ : ext::elementwise_<bits_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bits_> parent;
    };
  }
  /*!
    Returns an unsigned integer value which has the same bits as the input

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = bits(x);
    @endcode

    is equivalent to:

    @code
    as_integer<T,unsigned> r = bitwase_cast< as_integer<T,unsigned>>(a0);
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bits_, bits, 1)
} }

#endif

