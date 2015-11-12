//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_NEGIFNOT_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_NEGIFNOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>



namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief negifnot generic tag

     Represents the negifnot function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct negifnot_ : ext::elementwise_<negifnot_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<negifnot_> parent;
    };
  }
  /*!
    The function returns -a1 if a0 is false and a1 otherwise.
    The two operands must have the same cardinal.

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T1 r = negifnot(a0,a1);
    @endcode

    is similar to:

    @code
    T1 r = a0 ? a1 : -a1;
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::negifnot_, negifnot, 2)
} }

#endif

