//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_REC_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief  fast_rec generic tag

      Represents the fast_rec function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fast_rec_ : ext::elementwise_<fast_rec_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_rec_> parent;
    };
  }
  /*!
    Computes the inverse its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = fast_rec(x);
    @endcode

    is similar to:

    @code
    T r = T(1)/x;
    @endcode

    @par Note:

    Fast means that the computation is possibly done through some
    low precision intrinsic. The result can be not fully accurate

    @param  a0

    @see funcref{rec}
    @return      a value of the typeof the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_rec_, fast_rec, 1)

} }

#endif
