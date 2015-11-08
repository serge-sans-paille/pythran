//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_MASK2LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_MASK2LOGICAL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>



namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief mask2logical generic tag

     Represents the mask2logical function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct mask2logical_ : ext::elementwise_<mask2logical_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<mask2logical_> parent;
    };
  }

  /*!
    The function converts an arithmetic mask where each element is
    Zero or Allbits to a logical value.
    If it is not the case this function asserts.

    @par Semantic:

    For every parameters of types respectively T0:

    @code
    as_logical<T0> r = mask2logical(a0);
    @endcode

    is similar to:

    @code
    as_logical<T0> r = logical(a0);
    @endcode

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mask2logical_, mask2logical, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mask2logical_, m2l, 1)
} }

#endif
