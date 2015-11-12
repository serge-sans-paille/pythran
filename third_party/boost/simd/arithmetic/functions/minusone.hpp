//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_MINUSONE_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_MINUSONE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  minusone generic tag

      Represents the minusone function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct minusone_ : ext::elementwise_<minusone_>
    {
      typedef ext::elementwise_<minusone_> parent;
    };
  }
  /*!
    Return the entry minus one, saturated in the entry type.
    If @c x is not Nan, @c minusone(x) is always less or equal to x.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = minusone(x);
    @endcode

    is similar to:

    @code
    T r = x-1
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minusone_, minusone, 1)
} }

#endif


