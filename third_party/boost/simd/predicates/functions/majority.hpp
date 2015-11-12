//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_MAJORITY_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_MAJORITY_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief majority generic tag

     Represents the majority function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct majority_ : ext::elementwise_<majority_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<majority_> parent;
    };}
  /*!
    Returns True if at least two inputs are not zero else False.

    @par Semantic:

    @code
    logical<T> r = majority(a0,a1,a2);
    @endcode

    is similar to:

    @code
    logical<T> r = (a0!= 0)+(a1!= 0)+(a2!= 0) >= 2;
    @endcode

    @param a0

    @param a1

    @param a2

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::majority_, majority, 3)
} }

#endif

