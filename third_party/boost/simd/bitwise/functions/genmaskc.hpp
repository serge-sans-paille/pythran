//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENMASKC_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENMASKC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  genmaskc generic tag

      Represents the genmaskc function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct genmaskc_ : ext::elementwise_<genmaskc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<genmaskc_> parent;
    };
  }
  /*!
    Returns a mask of bits. All ones if the
    input element is zero else all zeros.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = genmaskc(x);
    @endcode

    is similar to

    @code
    T r = x ? Zero : Allbits;
    @endcode

    @par Alias:
    @c typed_maskc, @c logical2maskc, @c l2mc, @c typed_maskc, @c if_zero_else_allbits

    @see @funcref{if_else_allbits}
    @param  a0

    @return      a value of the type of the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmaskc_, genmaskc, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmaskc_, typed_maskc, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmaskc_, logical2maskc, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmaskc_, l2mc, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::genmaskc_, if_zero_else_allbits, 1)
} }

#endif
