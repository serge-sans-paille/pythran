//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ONEPLUS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ONEPLUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
  /*!
      @brief  oneplus generic tag

      Represents the oneplus function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct oneplus_ : ext::elementwise_<oneplus_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<oneplus_> parent;
    };
  }
  /*!
    Returns the one plus the entry, saturated in the entry type.
    If @c x is not Nan, @c oneplus(x) is greater or equal to x.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = oneplus(x);
    @endcode

    The code is similar to:

    @code
    T r = 1+x
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::oneplus_, oneplus, 1)
} }

#endif


