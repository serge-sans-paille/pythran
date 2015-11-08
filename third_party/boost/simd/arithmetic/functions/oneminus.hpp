//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ONEMINUS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ONEMINUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  oneminus generic tag

      Represents the oneminus function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct oneminus_ : ext::elementwise_<oneminus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<oneminus_> parent;
    };
  }
  /*!
    Returns the one minus the entry, saturated in the entry type.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = oneminus(x);
    @endcode

    For signed type is similar to:

    @code
    T r = 1-x
    @endcode

    For unsigned type it is equivalent (due to saturation) to:

    @code
    T r = x == 0 ? 1 : 0
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::oneminus_, oneminus, 1)
} }

#endif


