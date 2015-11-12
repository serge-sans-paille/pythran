//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIST_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIST_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  dist generic tag

      Represents the dist function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct dist_ : ext::elementwise_<dist_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<dist_> parent;
    };
  }
  /*!
    Computes the (saturated) absolute value of the difference of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = dist(x, y);
    @endcode

    is similar to:

    @code
    T r = abs(x-y);
    @endcode

    @par Note

    The result is never negative. For floating, it can of course be Nan.

    @see  @funcref{ulpdist}
    @param  a0

    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::dist_, dist, 2)
} }

#endif
