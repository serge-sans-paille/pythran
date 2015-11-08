//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FMA_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  fma generic tag

      Represents the fma function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fma_ : ext::elementwise_<fma_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fma_> parent;
    };
  }
  /*!
    Computes the (fused) multiply add of the three parameters.

    @par semantic:
    For any given value @c x,  @c y,  @c z of type @c T:

    @code
    T r = fma(x, y, z);
    @endcode

    The code is similar to:

    @code
    T r = x*y+z;
    @endcode

    @par Note
    Correct fused multiply/add implies

    1) only one rounding

    2) no "intermediate" overflow

    fma provides this each time it is reasonable
    in terms of performance (mainly if the system has the hard
    wired capability).
    If you need fma in all circumstances in your own
    code use correct_fma.

    @par Alias

    @c madd

    @param  a0
    @param  a1
    @param  a2

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fma_, fma, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fma_, madd, 3)

  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fma_, fam, 3)
  {
    typename boost::dispatch::make_functor<tag::fma_, A0>::type callee;
    return callee(a1, a2, a0);
  }

  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fma_, amul, 3)
  {
    typename boost::dispatch::make_functor<tag::fma_, A0>::type callee;
    return callee(a1, a2, a0);
  }

} }

#endif
