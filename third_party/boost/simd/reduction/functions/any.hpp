//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_ANY_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_ANY_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief any generic tag

     Represents the any function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logical_or_;
    struct False;

    struct any_ : ext::reduction_<any_, tag::logical_or_, tag::False>
    {
      /// @brief Parent hierarchy
      typedef ext::reduction_<any_, tag::logical_or_, tag::False> parent;
    };
  }
  /*!
    Returns true if at least one element of the input vector is non zero.

    @par Semantic:

    For every parameter of type T0

    @code
    logical<scalar_of<T0>> r = any(a0);
    @endcode

    is similar to:

    @code
    logical<scalar_of<T0>> r = False;
    for(result_type i = 0; i != cardinal_of<T0>; ++i)
      if (a0[i]) {r =  True; break; }
    @endcode

    @param a0

    @return a value of the scalar type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::any_, any, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::any_, any, 2)
} }
#endif
