//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_RAW_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_RAW_REC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief  raw_rec generic tag

      Represents the raw_rec function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct raw_rec_ : ext::elementwise_<raw_rec_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<raw_rec_> parent;
    };
  }
  /*!
    Computes an rough approximation of the inverse of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = raw_rec(x);
    @endcode

    is similar to:

    @code
    T r = T(1)/x;
    @endcode

    @par Note:

    Raw means that the computation is possibly done with the most speed available
    on current hardware but with the least precision.

    @param  a0

    @see funcref{rec}
    @see funcref{fast_rec}

    @return      a value of the type of the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::raw_rec_, raw_rec, 1)

} }

#endif
