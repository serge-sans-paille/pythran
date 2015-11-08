//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FNMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FNMA_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  fnma generic tag

      Represents the fnma function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fnma_ : ext::elementwise_<fnma_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fnma_> parent;
    };
  }

  /*!
    Computes the fused negated multiply-add of three values.

    @par semantic:
    For any given value @c x,  @c y,  @c z of type @c T:

    @code
    T r = fnma(x, y, z);
    @endcode

    The code is similar to:

    @code
    T r = -(x*y+z);
    @endcode

    @param  a0
    @param  a1
    @param  a2

    @return a value of the same type as the input.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fnma_, fnma, 3)

  /*!
    Computes the fused negated add-multiply of three values.

    @par semantic:
    For any given value @c x,  @c y,  @c z of type @c T:

    @code
    T r = fnam(x, y, z);
    @endcode

    The code is similar to:

    @code
    T r = -(x+y*z);
    @endcode

    @param  a0
    @param  a1
    @param  a2

    @return a value of the same type as the input.
  **/
  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fnma_, fnam, 3)
  {
    typename boost::dispatch::make_functor<tag::fnma_, A0>::type callee;
    return callee(a2, a1, a0);
  }
} }

#endif
