//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_KNUTH_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_KNUTH_EQUAL_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief knuth_equal generic tag

     Represents the knuth_equal function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct knuth_equal_ : ext::elementwise_<knuth_equal_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<knuth_equal_> parent;
    };
  }
  /*!
    \f$|a_0-a_1| \le a_2*\mathop{\mathrm{exponent(\max(|a_0|, |a_1|))}}\f$

    @par Semantic:

    For every parameters of floating type T0:

    @code
    logical<T0> r = knuth_equal(a0,a1,a2);
    @endcode

    is similar to:

    @code
    logical<T0> r = abs(a0-a1) <= a2*pow2(exponent(max(abs(a0), abs(a1))));
    @endcode

    @param a0

    @param a1

    @param a2

    @return a logical value  of the type associated the first parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::knuth_equal_, knuth_equal, 3)
}

#endif

