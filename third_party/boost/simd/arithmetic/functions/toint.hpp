//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOINT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  toint generic tag

      Represents the toint function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct toint_ : ext::elementwise_<toint_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<toint_> parent;
    };
  }
  /*!
    Convert to integer by truncation.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T> r = toint(x);
    @endcode

    The code is similar to:

    @code
    as_integer<T> r = static_cast<as_integer<T> >(x)
    @endcode

    @par Notes:

    @c toint cast a floating value to the signed integer value of the same bit size.

    This is done by C casting for scalars and corresponding intrinsic in simd (if available).

    Peculiarly,  that implies that the behaviour of this function on invalid entries is
    not defined and quite unpredictable.

    (For instance it is quite frequent that the test:

    @code
    toint(Inf<double>()) ==  toint(1.0/0.0)
    @endcode


    will return false whilst the test:

    @code
    Inf<double>() == 1.0/0.0
    @endcode


    returns true !)

    If you intend to use nans and infs entries,  consider using toints instead.
    On integral typed values, it acts as identity.

    @par Alias

    fast_toint

    @param  a0

    @return      a value of the integer type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toint_, toint, 1)

} }

#include <boost/simd/operator/specific/common.hpp>

#endif
