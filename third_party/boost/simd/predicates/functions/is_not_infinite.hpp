//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_NOT_INFINITE_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_NOT_INFINITE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_not_infinite generic tag

     Represents the is_not_infinite function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_not_infinite_ : ext::elementwise_<is_not_infinite_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_not_infinite_> parent;
    };}
  /*!
    TODO Put description here

    @par Semantic:

    @code
    logical<T> r = is_not_infinite(a0);
    @endcode

    is similar to:

    @code
    if T is floating
      logical<T> r = (a0 !=  Inf) && (a0 != -Inf);
    else
      logical<T> r = True;
    @endcode

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_infinite_, is_not_infinite, 1)
} }

#endif

