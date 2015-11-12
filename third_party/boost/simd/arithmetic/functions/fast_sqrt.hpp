//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_SQRT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief fast_sqrt generic tag

      Represents the fast_sqrt function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fast_sqrt_ : ext::elementwise_<fast_sqrt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_sqrt_> parent;
    };
  }
 /*!
    Computes the square root of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = fast_sqrt(x);
    @endcode

    is similar to:

    @code
    T r = sqrt(x);
    @endcode

    @par Note:

    Fast means that the computation is possibly done through some
    low precision intrinsic. The result can be not fully accurate

    @see funcref{sqrt}
    @param  a0

    @return      a value of the typeof the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_sqrt_, fast_sqrt, 1)
} }

#endif
