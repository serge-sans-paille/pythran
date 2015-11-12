//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_IFLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_IFLOOR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  ifloor generic tag

      Represents the ifloor function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct ifloor_ : ext::elementwise_<ifloor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ifloor_> parent;
    };
  }
  /*!
    Computes the integer conversion of the floor of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T> r = ifloor(x);
    @endcode

    is equivalent to:

    @code
    as_integer<T> r = toints(floor(x));
    @endcode

    @par Note:
    This operation is properly saturated

    @see funcref{fast_ifloor}
    @param  a0

    @return an integral value of the integral type associated to the input.


  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ifloor_, ifloor, 1)
} }

#endif


