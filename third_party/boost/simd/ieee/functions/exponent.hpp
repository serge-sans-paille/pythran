//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_EXPONENT_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_EXPONENT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief exponent generic tag

     Represents the exponent function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct exponent_ : ext::elementwise_<exponent_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<exponent_> parent;
    };
  }
  /*!
    Returns the exponent of the floating input.
    \par

    @par Semantic:

    @code
    as_integer<T> r = exponent(a0);
    @endcode

    is similar to:

    @code
    as_integer<T> r = ilogb(a0);
    @endcode

    @par Note:

     The sign \f$ \pm \f$ , exponent e and mantissa m of a floating point entry a are related by
    \f$a = \pm m\times 2^e\f$, with m between one (included) and two (excluded).
    For integral type inputs exponent is always 0 and mantissa reduces to identity.

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::exponent_, exponent, 1)
} }

#endif
