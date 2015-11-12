//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ICEIL_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ICEIL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  iceil generic tag

      Represents the iceil function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct iceil_ : ext::elementwise_<iceil_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<iceil_> parent;
    };
  }
  /*!
    Computes the integer conversion of the ceil of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T> r = iceil(x);
    @endcode

    is equivalent to:

    @code
    as_integer<T> r = toints(ceil(x));
    @endcode

    @par Note:
    This operation is properly saturated

    @see funcref{fast_iceil}
    @param  a0

    @return an integral value of the integral type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::iceil_, iceil, 1)
} }

#endif


