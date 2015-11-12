//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_POPCNT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_POPCNT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  popcnt generic tag

      Represents the popcnt function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct popcnt_ : ext::elementwise_<popcnt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<popcnt_> parent;
    };
  }
  /*!
    Returns the number of bit sets the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T, unsigned> r = popcnt(x);
    @endcode

    @see  @funcref{clz}, @funcref{ctz}
    @param  a0

    @return      a value of the unsigned integer
                 type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::popcnt_, popcnt, 1)
} }
#endif
