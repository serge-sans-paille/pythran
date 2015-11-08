//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ALLBITS_ELSE_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_IF_ALLBITS_ELSE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief if_allbits_else generic tag

     Represents the if_allbits_else function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct if_allbits_else_ : ext::elementwise_<if_allbits_else_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<if_allbits_else_> parent;
    };
  }

  /*!
    If a0 is true returns allbits else returns a1

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T1 r = if_allbits_else(a0,a1);
    @endcode

    is similar to:

    @code
    T r = a0 ? Allbits : a1;
    @endcode

    @par Alias:
    @c if_allbits_else,
    @c ifallbitselse,
    @c ifnot_else_allbits,
    @c ifnotelseallbits,
    @c if_nan_else,
    @c ifnanelse,
    @c ifnot_else_nan,
    @c ifnotelsenan

    @see @funcref{genmask}
    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, if_allbits_else, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, ifallbitselse, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, ifnot_else_allbits, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, ifnotelseallbits, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, if_nan_else, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, ifnanelse, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, ifnot_else_nan, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_allbits_else_, ifnotelsenan, 2)
} }

#endif


