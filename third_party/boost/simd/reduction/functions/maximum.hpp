//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_MAXIMUM_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/include/constants/maxinit.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief maximum generic tag

     Represents the maximum function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct max_;
    struct Maxinit;

    struct maximum_ : ext::reduction_<maximum_, tag::max_, tag::Maxinit>
    {
      /// @brief Parent hierarchy
      typedef ext::reduction_<maximum_, tag::max_, tag::Maxinit> parent;
    };
  }
  /*!
    Returns the greatest element of the SIMD vector

    @par Semantic:

    For every parameter of type T0

    @code
    scalar_of<T0> r = maximum(a0);
    @endcode

    is similar to:

    @code
      scalar_of<T0> r = Minf;
      for(std::size_t i=0;i<cardinal_of<T0>;++i)
        r =  r < a0[i] ? a0[i] : r;
    @endcode

    @param a0

    @return a value of the scalar type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::maximum_, maximum, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::maximum_, maximum, 2)
} }
#endif

