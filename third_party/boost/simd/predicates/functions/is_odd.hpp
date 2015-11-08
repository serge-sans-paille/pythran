//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_ODD_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_ODD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_odd generic tag

     Represents the is_odd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_odd_ : ext::elementwise_<is_odd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_odd_> parent;
    };}
  /*!
    Returns True or False according a0 is odd or not.

    @par Semantic:

    @code
    logical<T> r = is_odd(a0);
    @endcode

    is similar to:

    @code
    logical<T> r = (abs(a0)/2)*2 == abs(a0)-1;
    @endcode

    @par Note:

    A floating number a0 is odd if a0-1 is even

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_odd_, is_odd, 1)
} }

#endif

