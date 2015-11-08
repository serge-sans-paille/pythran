//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief modf generic tag

     Represents the modf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct modf_ : ext::elementwise_<modf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<modf_> parent;
    };
  }
  /*!
    Returns the integer and the fractionnal part of the input

    @par Semantic:

    @code
    tie(t, f) = modf(x);
    @endcode

    is similar to:

    @code
    T t = trunc(x);
    T r = frac(x);
    @endcode

    @param a0 Value to decompose

    @return  A pair containing the integer and fractionnal part of @c a0
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::modf_, modf, 1)

  /*!
    Computes the integer and the fractionnal part of the input

    @par Semantic:

    @code
    f = modf(x, t);
    @endcode

    is similar to:

    @code
    T t = trunc(x);
    T f = frac(x);
    @endcode

    @param a0 Value to decompose
    @param a1 L-Value that will receive the fractionnal part of a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&),2)
  /*!
    Computes the integer and the fractionnal part of the input

    @par Semantic:

    @code
    modf(x, t, f);
    @endcode

    is similar to:

    @code
    T t = trunc(x);
    T f = frac(x);
    @endcode

    @param a0 Value to decompose
    @param a1 L-Value that will receive the fractionnal part of @c a0
    @param a2 L-Value that will receive the integer part of @c a0

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&)(A1&),2)


} }

#endif
