//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOUINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_TOUINTS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  touints generic tag

      Represents the touints function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct touints_ : ext::elementwise_<touints_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<touints_> parent;
    };
  }
  /*!
    Convert to unsigned integer by saturated truncation.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T, unsigned> r = touint(x);
    @endcode

    The code is similar to:

    @code
    as_integer<T,unsigned> r = static_cast<as_integer<T,unsigned> >(saturate<as_integer<T,unsigned> (x)))
    @endcode

    @par Notes:

    The Inf, Nan and negative values are treated properly and go respectively to
    Valmax, and Zero of the destination integral type.

    All values superior (resp. less) than Valmax (resp. Valmin) of the return type
    are saturated accordingly.

    @par Alias

    saturated_toint

    @see @funcref{toint}
    @param  a0

    @return      a value of the unsigned integer type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::touints_, touints, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::touints_, saturated_touint, 1)

} }

#endif

