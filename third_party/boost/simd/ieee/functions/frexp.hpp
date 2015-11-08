//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_FREXP_HPP_INCLUDED

/*!
  @file
  @brief Definition of frexp function
**/

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

// Fixup for some library defining this a bit liberally
#ifdef frexp
#undef frexp
#endif

namespace boost { namespace simd
{
  namespace tag
  {
    /// @brief Hierarchy tag for frexp function
    struct frexp_ : ext::elementwise_<frexp_>
    {
      typedef ext::elementwise_<frexp_> parent;
    };
  }


  /*!
    Returns the mantissa and exponent of the input

    @par Semantic:

    @code
    tie(m, e) = frexp(x);
    @endcode

    is similar to:

    @code
    as_integer<T > e = exponent(x)+1;
    T m = mantissa(x)/2;
    @endcode

    @par Note:

    @c frexp splits a floating point value @c v f in its signed mantissa @c m and
    exponent @c e so that

    @f$v = m\times 2^e@f$

    with absolute value of @c m between 0.5 (included) and 1 (excluded)

    @see @funcref{exponent},  @funcref{mantissa}
    @param a0 Value to decompose
    @return A pair containing the signed mantissa and exponent of @c a0

    @return The mantissa of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::frexp_, frexp, 1)


  /*!
    Returns the mantissa computes the exponent of the input

    @code
    m = frexp(x, e);
    @endcode

    is similar to:

    @code
    as_integer<T > e = exponent(x)+1;
    T m = mantissa(x)/2;
    @endcode

    @par Note:

    @c frexp splits a floating point value @c v f in its signed mantissa @c m and
    exponent @c e so that

    @f$v = m\times 2^e@f$

    with absolute value of @c m between 0.5 (included) and 1 (excluded)

    @see @funcref{exponent},  @funcref{mantissa}
    @param a0 Value to decompose
    @param a1 L-Value that will receive the exponent of @c a0
    @return The mantissa of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::frexp_, frexp
                                            , (A0 const&)(A1&), 2
                                            )

  /*!
    Computes the mantissa and the exponent of the input

    @code
    m = frexp(x, e);
    @endcode

    is similar to:

    @code
    as_integer<T > e = exponent(x)+1;
    T m = mantissa(x)/2;
    @endcode

    @par Note:

    @c frexp splits a floating point value @c v f in its signed mantissa @c m and
    exponent @c e so that

    @f$v = m\times 2^e@f$

    with absolute value of @c m between 0.5 (included) and 1 (excluded)

    @see @funcref{exponent},  @funcref{mantissa}
    @param a0 Value to decompose
    @param a1 L-Value that will receive the mantissa of @c a0
    @param a2 L-Value that will receive the exponent of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::frexp_, frexp
                                            , (A0 const&)(A1&)(A2&), 3
                                            )
} }

#endif
