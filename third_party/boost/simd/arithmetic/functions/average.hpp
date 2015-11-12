//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_AVERAGE_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_AVERAGE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  average generic tag

      Represents the average function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct average_ : ext::elementwise_<average_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<average_> parent;
    };
  }
  /*!
    Computes the arithmetic mean of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = average(x, y);
    @endcode

    For floating point values the code is equivalent to:

    @code
    T r = (x+y)/T(2);
    @endcode

    for integer types  it returns a rounded value at a distance guaranteed
    less or equal to 0.5 of the average floating value,  but can differ
    of one unity from the truncation given by (x1+x2)/T(2).

    @par Note:

    This function does not overflow.

    @see  @funcref{meanof}
    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::average_, average, 2)
} }

#endif
