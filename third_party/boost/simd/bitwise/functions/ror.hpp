//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_ROR_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_ROR_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  ror generic tag

      Represents the ror function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct ror_ : ext::elementwise_<ror_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ror_> parent;
    };
  }
  /*!
    Returns the first entry rotated right
    by the absolute value of the second entry.

    @par semantic:
    For any given value @c x of type @c T, n  of type @c I:

    @code
    T r = ror(x, n);
    @endcode

    @see  @funcref{rol}, @funcref{rror}, @funcref{rrol}
    @param  a0
    @param  a1

    @return      a value of the same type as the first input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ror_, ror, 2)
} }
#endif
