//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_NONE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_NONE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief none generic tag

     Represents the none function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct none_ : dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef dispatch::tag::formal_ parent;
    };
  }
  /*!
    Returns True if all elements of the input vector are zero.

    @par Semantic:

    For every parameter of type T0

    @code
    as_logical<scalar_of<T0>> r = none(a0);
    @endcode

    is similar to:

    @code
    as_logical<scalar_of<T0>> r = !any(a0);
    @endcode

    @param a0

    @return a value of the scalar logical type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::none_, none, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::none_, none, 2)
} }
#endif
