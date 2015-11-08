//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_FAST_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_FAST_FREXP_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief fast_frexp generic tag

     Represents the fast_frexp function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_frexp_ : ext::elementwise_<fast_frexp_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_frexp_> parent;
    };
  }

  /*!
    Returns the mantissa and exponent of the input

    @par Semantic:

    @code
    tie(m, e) = fast_frexp(x);
    @endcode

    is similar to:

    @code
    as_integer<T > e = exponent(x)+1;
    T m = mantissa(x)/2;
    @endcode

    @par Note:
    The fast prefix indicates that, for speed consideration, the result may be
    incorrect for special values like inf, -inf nan and zero that deserve
    special treatment. If you are not sure use @funcref{frexp} at the expense of some
    more machine cycles.

    @see  @funcref{frexp}
    @param a0 Value to decompose

    @return A pair containing the signed mantissa and exponent of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_frexp_, fast_frexp, 1)

  /*!
    Returns the mantissa computes the  exponent of the input

    @code
    m = fast_frexp(x, e);
    @endcode

    is similar to:

    @code
    as_integer<T > e = exponent(x)+1;
    T m = mantissa(x)/2;
    @endcode

    @par Note:

    @par Note:
    The fast prefix indicates that for speed sake
    the result may be incorrect for limiting values:
    inf, -inf nan and zero that deserve special treatment.
    If you are not sure use @c frexp at the expense
    of some more machine cycles.

    @param a0 Value to decompose
    @param a1 L-Value that will receive the exponent of @c a0
    @return The mantissa of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::fast_frexp_
                                            , fast_frexp,(A0 const&)(A1&)
                                            , 2
                                            )

  /*!
    Computes the mantissa and the  exponent of the input

    @code
    m = fast_frexp(x, e);
    @endcode

    is similar to:

    @code
    as_integer<T > e = exponent(x)+1;
    T m = mantissa(x)/2;
    @endcode

    @par Note:

    @par Note:
    The fast prefix indicates that for speed sake
    the result may be incorrect for limiting values:
    inf, -inf nan and zero that deserve special treatment.
    If you are not sure use @c frexp at the expense
    of some more machine cycles.

    @param a0 Value to decompose
    @param a1 L-Value that will receive the mantissa of @c a0
    @param a2 L-Value that will receive the exponent of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::fast_frexp_
                                            , fast_frexp,(A0 const&)(A0&)(A1&)
                                            , 2
                                            )
} }

#endif
