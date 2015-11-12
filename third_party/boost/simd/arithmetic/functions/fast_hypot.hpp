//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_HYPOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  fast_hypot generic tag

      Represents the fast_hypot function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fast_hypot_ : ext::elementwise_<fast_hypot_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_hypot_> parent;
    };
  }
  /*!
    Computes \f$(x^2 + y^2)^{1/2}\f$

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = fast_hypot(x, y);
    @endcode

    The code is equivalent to:

    @code
    T r =sqrt(sqr(x)+sqr(y));
    @endcode

    Fast means that nothing is done to avoid overflow or inaccuracies
    for large values. See @funcref{hypot} if that matters.

    @param  a0
    @param  a1

    @return      a value of the same floating type as the input.
  **/

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_hypot_, fast_hypot, 2)
} }

#endif


