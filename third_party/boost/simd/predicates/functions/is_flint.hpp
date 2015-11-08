//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_FLINT_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_FLINT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_flint generic tag

     Represents the is_flint function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_flint_ : ext::elementwise_<is_flint_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_flint_> parent;
    };}
  /*!
    Returns True or False according a0 is a flint or not.

    @par Semantic:

    @code
    logical<T> r = is_flint(a0);
    @endcode

    @par Note:

    A flint is a 'floating integer' i.e. a floating number
    representing exactly an integer value.

    Be conscious that all sufficiently great floating points values
    are flint and even are even...

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_flint_, is_flint, 1)
} }

#endif

