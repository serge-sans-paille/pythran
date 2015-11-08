//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_UNORD_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_UNORD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_unord generic tag

     Represents the is_unord function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_unord_ : ext::elementwise_<is_unord_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_unord_> parent;
    };}
  /*!
    Returns True if a0 or a1 is nan.

    @par Semantic:

    @code
    logical<T> r = is_unord(a0,a1);
    @endcode

    is similar to:

    @code
    logical<T> r = (a0 != a0) || (a1 != a1);
    @endcode

    @param a0

    @param a1

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_unord_, is_unord, 2)
} }

#endif

