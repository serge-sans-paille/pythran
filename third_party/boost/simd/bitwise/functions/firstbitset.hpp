//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_FIRSTBITSET_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_FIRSTBITSET_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  firstbitset generic tag

      Represents the firstbitset function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct firstbitset_ : ext::elementwise_<firstbitset_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<firstbitset_> parent;
    };
  }
  /*!
    Returns the bit pattern in which the only bit set is
    the first bit set (beginning with the least significant bit) in the parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T,unsigned> r = firstbitset(x);
    @endcode

    @see  @funcref{ffs},  @funcref{firstbitunset}
    @param  a0

    @return      a value unsigned integral type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::firstbitset_, firstbitset, 1)
} }

#endif
