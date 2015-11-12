//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_MINMOD_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_MINMOD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  minmod generic tag

      Represents the minmod function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct minmod_ : ext::elementwise_<minmod_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<minmod_> parent;
    };
  }
  /*!
    Return the minimum of the two entries
    if they have the same sign, otherwise 0

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = minmod(x, y);
    @endcode

    is similar to:

    @code
    T r =  x*y > 0 ? min(x, y) : 0;
    @endcode

    @param  a0
    @param  a1

    @return      a value of the same type as the inputs.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minmod_, minmod, 2)
} }

#endif


