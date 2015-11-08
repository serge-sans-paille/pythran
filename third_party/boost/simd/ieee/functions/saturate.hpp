//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SATURATE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief saturate generic tag

      Represents the saturate function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct saturate_ : ext::elementwise_<saturate_>
    {
      /// @brief parent Hierarchy
      typedef ext::elementwise_<saturate_> parent;
    };
  }

  /*!

    Saturate a value of type @c T with the limit values of type @c S.

    @par Semantic:

    @code
    T r = saturate(x, as_<S>())
    @endcode

    is similar to:

    @code
    if (a0 > Inf<S>()) r =  T(Inf<S>());
    else if  (a0 <  Minf<S>()) r =  T(Minf<S>());
    else r = a0;
    @endcode

    @par Note:
    Note that the functor is only valid if conceptually the type S is included in type T
    (or the contrary but this case leads to identity)

    @param a0 Value to saturate
    @param a1 Type specifier of the saturation limit

    @return  The input value saturated on limit of the type specifier
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::saturate_, saturate, 2)

  /*!
    Returns the saturated value of the first input in the template parameter type,
    but in the same type as the input.

    @par Semantic:

    @code
    T r = saturate<S>(x)
    @endcode

    is similar to:

    @code
    if (a0 > Inf<S>()) r =  T(Inf<S>());
    else if  (a0 <  Minf<S>()) r =  T(Minf<S>());
    else r = a0;
    @endcode

    @param a0

    @return a value of same type as the inputs
  **/
  template<class T,class A0> BOOST_FORCEINLINE
  typename boost::dispatch::meta::
                  call< tag::saturate_( A0 const&
                                      , boost::dispatch::meta::as_<T>
                                      )
                      >::type
  saturate(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::saturate_, A0>::type callee;
    return callee(a0,boost::dispatch::meta::as_<T>());
  }
} }

#endif
