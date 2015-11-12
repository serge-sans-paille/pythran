//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_NGTZ_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_NGTZ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_ngtz generic tag

     Represents the is_ngtz function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_ngtz_ : ext::elementwise_<is_ngtz_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_ngtz_> parent;
    };}
  /*!
    Returns True if a0 is not greater than zero else returns False.

    @par Semantic:

    @code
    logical<T> r = is_ngtz(a0);
    @endcode

    is similar to:

    @code
    logical<T> r = !(a0 > 0);
    @endcode

    @par Note:

    Due to existence of nan, this is not equivalent to @c is_lez(a0)
    for floating types

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_ngtz_, is_ngtz, 1)
} }

#endif

