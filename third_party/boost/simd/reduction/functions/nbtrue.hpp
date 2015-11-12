//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_NBTRUE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief nbtrue generic tag

     Represents the nbtrue function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct nbtrue_ : ext::unspecified_<nbtrue_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<nbtrue_> parent;
    };
  }
  /*!
    Returns the number of non zero elements of the input SIMD vector.

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = nbtrue(a0);
    @endcode

    is similar to:

    @code
    T0 r = sum(if_one_else_zero(a0));
    @endcode

    @param a0

    @return a value of the scalar type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::nbtrue_, nbtrue, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::nbtrue_, nbtrue, 2)
} }
#endif

