//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_EVEN_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_EVEN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_even generic tag

     Represents the is_even function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_even_ : ext::elementwise_<is_even_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_even_> parent;
    };}
  /*!
    Returns True or False according a0 is even or not.

    @par Semantic:

    @code
    logical<T> r = is_even(a0);
    @endcode

    is similar to:

    @code
    logical<T> r = int(a0/2)*2 == a0;
    @endcode

    @par Note:

    A floating number is even if it is a  flint
    and divided by two it is still a flint.

    A flint is a 'floating integer' i.e. a floating number
    representing an integer value

    Be conscious that all sufficiently great floating points values are even...

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_even_, is_even, 1)
} }

#endif

