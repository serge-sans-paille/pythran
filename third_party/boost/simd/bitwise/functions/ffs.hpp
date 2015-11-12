//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  ffs generic tag

      Represents the ffs function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct ffs_ : ext::elementwise_<ffs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ffs_> parent;
    };
  }
  /*!
    returns the index
    of the first bit set (beginning with the least
    significant bit) in the parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T,unsigned> r = ffs(x);
    @endcode

    @see  @funcref{firstbitset},  @funcref{firstbitunset}
    @param  a0

    @return      a value unsigned integral type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ffs_, ffs, 1)
} }

#endif
