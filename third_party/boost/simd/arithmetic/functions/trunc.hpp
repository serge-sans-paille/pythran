//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TRUNC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TRUNC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  trunc generic tag

      Represents the trunc function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct trunc_ : ext::elementwise_<trunc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<trunc_> parent;
    };
  }
  /*!
    Computes the truncation toward zero of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = trunc(x);
    @endcode

    The code is similar to:

    @code
    T r = sign(x)*floor(abs(x));
    @endcode

    @par Note:

    For floating point number it is also one of the two ouputs of
    the modf function.
    And we have:

    @code
    trunc(x) + frac(x) == x;
    @endcode

    except for nans

    @par Alias

    fix

    @see @funcref{abs}, @funcref{frac}, @funcref{floor}, @funcref{sign}
    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::trunc_, trunc, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::trunc_, fix, 1)
} }

#endif
