//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_IS_SIMD_LOGICAL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_simd_logical generic tag

     Represents the is_simd_logical function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_simd_logical_ : ext::unspecified_<is_simd_logical_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<is_simd_logical_> parent;
    };
  }
  /*!
    returns true if all vector elements have all or no bit sets.

    @par Semantic:

    For every parameter of type T0

    @code
    logical<scalar_of<T0>> r = is_simd_logical(a0);
    @endcode

    is similar to:

    @code
    T0 r = all(a0 == Allbits || a0 == Zero);
    @endcode

    @param a0

    @return a value of the scalar logical type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_simd_logical_, is_simd_logical, 1)
} }
#endif

