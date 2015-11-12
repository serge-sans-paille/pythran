//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_LEZ_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_LEZ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_lez generic tag

     Represents the is_lez function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_lez_ : ext::elementwise_<is_lez_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_lez_> parent;
    };}
  /*!
    Returns True or False according a0 is less or equal to zero or not.

    @par Semantic:

    @code
    logical<T> r = is_lez(a0);
    @endcode

    is similar to:

    @code
    logical<T> r = a0 <= 0;
    @endcode

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_lez_, is_lez, 1)
} }

#endif

