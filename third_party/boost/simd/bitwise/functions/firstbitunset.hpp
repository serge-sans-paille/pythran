//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_FIRSTBITUNSET_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_FIRSTBITUNSET_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  firstbitunset generic tag

      Represents the firstbitunset function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct firstbitunset_ : ext::elementwise_<firstbitunset_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<firstbitunset_> parent;
    };
  }
  /*!
    Returns the bit pattern in which the only bit set is
    the first bit unset (beginning with the least significant bit) in the parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T,unsigned> r = firstbitunset(x);
    @endcode

    @see  @funcref{ffs},  @funcref{firstbitset}
    @param  a0

    @return      a value unsigned integral type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::firstbitunset_, firstbitunset, 1)
} }

#endif

