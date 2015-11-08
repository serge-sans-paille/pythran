//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_TWOPOWER_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_TWOPOWER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  twopower generic tag

      Represents the twopower function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct twopower_ : ext::elementwise_<twopower_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<twopower_> parent;
    };
  }

  /*!
    Returns \f$2^n\f$ (0 if n is less than zero)

    @par semantic:
    For any given value n  of integral type @c I:

    @code
    T r = twopower(n);
    @endcode

    code is similar to:

    @code
    T r = 1 << n;
    @endcode

    @par Note:

    This function is not defined for floating entries

    @see  @funcref{ilog2}
    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::twopower_, twopower, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::twopower_, iexp2, 1)
} }
#endif
