//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIVS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_DIVS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  divs generic tag

      Represents the divs function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct divs_ : ext::elementwise_<divs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<divs_> parent;
    };
  }
  /*!
    Computes  the truncated saturated division of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = divs(x, y);
    @endcode

    The code is similar to:

    @code
    T r = trunc(x/y);
    @endcode

    for integral types, if y is null, it returns Valmax or Valmin
    if x is positive (resp. negative) and 0 if x is null.
    Saturated means that for signed integer types,
    @c divs(Valmin,-1) returns Valmax.

    @par Alias

    @c saturated_div, rdivide

    @see  @funcref{divides}, @funcref{fast_divides}, @funcref{rec}, @funcref{fast_rec}, @funcref{divfloor},
    @funcref{divceil}, @funcref{divround}, @funcref{divround2even}, @funcref{divfix}
    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, divs, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, saturated_div, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, rdivide, 2)

  template<class A0, class A1>
  BOOST_FORCEINLINE
  typename dispatch::meta::call<tag::divs_(A0, A1)>::type
  ldivide(A0 const& a0, A1 const& a1)
  {
    return dispatch::make_functor<tag::divs_, A0>::type()(a1, a0);
  }

  template<class A0, class A1>
  BOOST_FORCEINLINE
  typename dispatch::meta::call<tag::divs_(A0, A1)>::type
  ldiv(A0 const& a0, A1 const& a1)
  {
    return dispatch::make_functor<tag::divs_, A0>::type()(a1, a0);
  }

} }

#endif
