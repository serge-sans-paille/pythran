//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/U.B.P.
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ. Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_CONJ_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_CONJ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  conj generic tag

      Represents the conj function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct conj_ : ext::elementwise_<conj_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<conj_> parent;
    };
  }
  /*!
    Computes the conjugate value of its parameter (identity for reals).

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = conj(x);
    @endcode

    for real parameters is equivalent to:

    @code
    T r = x
    @endcode

    @par Alias

    conjugate

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::conj_, conj, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::conj_, conjugate, 1)
} }

#endif

