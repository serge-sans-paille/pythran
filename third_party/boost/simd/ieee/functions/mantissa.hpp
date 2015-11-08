//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_MANTISSA_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_MANTISSA_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief mantissa generic tag

     Represents the mantissa function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct mantissa_ : ext::elementwise_<mantissa_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<mantissa_> parent;
    };
  }
  /*!
    Returns the signed mantissa of the floating input.
    \par
    The exponent e and signed mantissa m of a floating point entry a are related by
    \f$a = m\times 2^e\f$, with the absolute value of m between one (included) ans two (excluded)

    @par Semantic:

    @code
    T r = mantissa(a0);
    @endcode

    is similar to:

    @code
    T r = a0*pow(2, -exponent(a0));
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mantissa_, mantissa, 1)
} }

#endif
