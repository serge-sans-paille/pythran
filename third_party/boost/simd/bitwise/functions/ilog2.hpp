//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_ILOG2_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_ILOG2_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  ilog2 generic tag

      Represents the ilog2 function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct ilog2_ : ext::elementwise_<ilog2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ilog2_> parent;
    };
  }
  /*!
    Returns the integer part of the base 2
    logarithm of the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T> r = ilog2(x);
    @endcode

    The code is similar to

    @code
    as_integer<T> r = toints(log2(x));
    @endcode

    @see  @funcref{twopower}, @funcref{exponent}
    @param  a0

    @return      a value of the integer
                 type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ilog2_, ilog2, 1)
} }

#endif
