//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_EXPONENTBITS_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_EXPONENTBITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief exponentbits generic tag

     Represents the exponentbits function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct exponentbits_ : ext::elementwise_<exponentbits_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exponentbits_> parent;
    };
  }
  /*!
    Returns the exponent bits of the floating input as an integer value.
    the other bits (sign and mantissa) are just masked.
    This function is not defined on integral types.

    @par Semantic:

    @code
    as_integer<T> r = exponentbits(x);
    @endcode

    is similar to

    @code
    as_integer<T> r = x&Exponentmask<T>();
    @endcode

    @param a0

    @return a value of the integral type associated to the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::exponentbits_, exponentbits, 1)
} }

#endif
