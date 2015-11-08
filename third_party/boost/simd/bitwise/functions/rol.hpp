//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_ROL_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_ROL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  rol generic tag

      Represents the rol function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct rol_ : ext::elementwise_<rol_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<rol_> parent;
    };
  }
  /*!
    Returns the first entry rotated left
    by the absolute value of the second entry.

    @par semantic:
    For any given value @c x of type @c T, n  of type @c I:

    @code
    T r = rol(x, n);
    @endcode

    @see  @funcref{ror}, @funcref{rrol}, @funcref{rror}
    @param  a0
    @param  a1

    @return      a value of the same type as the first input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rol_, rol, 2)
} }

#endif
