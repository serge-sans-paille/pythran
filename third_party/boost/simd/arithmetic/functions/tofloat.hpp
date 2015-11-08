//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOFLOAT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  tofloat generic tag

      Represents the tofloat function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct tofloat_ : ext::elementwise_<tofloat_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tofloat_> parent;
    };
  }
  /*!
    Convert to floating point value.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_floating<T> r = tofloat(x);
    @endcode

    The code is similar to:

    @code
    as_floating<T> r = static_cast < as_floating<T> >(x)
    @endcode

    @param  a0

    @return      a value of the floating  type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tofloat_, tofloat, 1)
} }

#include <boost/simd/operator/specific/common.hpp>

#endif
