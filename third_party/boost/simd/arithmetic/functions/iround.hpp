//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_IROUND_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_IROUND_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  iround generic tag

      Represents the iround function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct iround_ : ext::elementwise_<iround_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<iround_> parent;
    };
  }
  /*!
    Computes the integer conversion of the round of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T> r = iround(x);
    @endcode

    is similar to:

    @code
    as_integer<T> r = toints(round(x));
    @endcode


    @see funcref{fast_iround}
    @param  a0

    @return an integral value of the integral type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::iround_, iround, 1)
} }

#endif


