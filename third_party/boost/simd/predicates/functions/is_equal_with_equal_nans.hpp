//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_equal_with_equal_nans generic tag

     Represents the is_equal_with_equal_nans function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_equal_with_equal_nans_ : ext::elementwise_<is_equal_with_equal_nans_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_equal_with_equal_nans_> parent;
    };}
  /*!
    Returns True or False according a0 and a1 are equal or not.
    nans are considered equal

    @par Semantic:

    @code
    logical<T> r = is_equal_with_equal_nans(a0,a1);
    @endcode

    is similar to:

    @code
    logical<T> r = (a0 == a1) || ((a0!= a0) && (a1!= a1));
    @endcode

    @param a0

    @param a1

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_equal_with_equal_nans_, is_equal_with_equal_nans, 2)
} }

#endif

