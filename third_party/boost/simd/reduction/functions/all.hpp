//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_ALL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_ALL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief all generic tag

     Represents the all function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct logical_and_;
    struct True;

    struct all_ : ext::reduction_<all_, tag::logical_and_, tag::True>
    {
      /// @brief Parent hierarchy
      typedef ext::reduction_<all_, tag::logical_and_, tag::True> parent;
    };
  }
  /*!
    Returns true if all elements of the input vector are non zero.

    @par Semantic:

    For every parameter of type T0

    @code
    logical<scalar_of<T0>> r = all(a0);
    @endcode

    is similar to:

    @code
    logical<scalar_of<T0>> r = True;
    for(result_type i = 0; i != meta::cardinal_of<T0>; ++i)
      if (!a0[i]) {r =  False; break; }
    @endcode

    @param a0

    @return a value of the scalar logical type asssociated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::all_, all, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::all_, all, 2)
} }
#endif

