//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FNMS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FNMS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  fnms generic tag

      Represents the fnms function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fnms_ : ext::elementwise_<fnms_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fnms_> parent;
    };
  }

  /*!
    Computes the fused negated multiply-substract of three values.

    @par semantic:
    For any given value @c x,  @c y,  @c z of type @c T:

    @code
    T r = fnms(x, y, z);
    @endcode

    The code is similar to:

    @code
    T r = -(x*y-z);
    @endcode

    @param  a0
    @param  a1
    @param  a2

    @return a value of the same type as the input.
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fnms_, fnms, 3)

  /*!
    Computes the fused substract-multiply of three value.

    @par semantic:
    For any given value @c x,  @c y,  @c z of type @c T:

    @code
    T r = fsm(x, y, z);
    @endcode

    The code is similar to:

    @code
    T r = x-y*z;
    @endcode

    @param  a0
    @param  a1
    @param  a2

    @return a value of the same type as the input.
  **/
  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fnms_, fsm, 3)
  {
    typename boost::dispatch::make_functor<tag::fnms_, A0>::type callee;
    return callee(a2, a1, a0);
  }
} }

#endif
