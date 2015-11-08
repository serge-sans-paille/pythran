//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_NEAREST_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_NEAREST_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief nearest generic tag

     Represents the nearest function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct nearest_ : ext::unspecified_<nearest_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<nearest_> parent;
    };
  }
  /*!
    one dimensional nearest interpolation
    \par

    @par Semantic:

    For every parameters expressions

    @code
    auto r = nearest(x, y, xi{, extrap});
    @endcode

    search the xi locations i  in x using bsearch and returns  y(j)
    choosing the one that realize the smallest distance of xi to x(j)
    if x is  in the interval [x(begin_), x(end_)]
    and depending on extrap value:

      - nan if extrap is missing or false
      - extrapolation if extrap is true (so x(begin_) or x(end_) accordingly)
      - value of extrap if the type of extrap is a scalar of
        the x element type

    @param a0
    @param a1
    @param a2
    @param a3

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::nearest_, nearest, 4)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::nearest_, nearest, 3)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::nearest_, Domain, N, Expr>
        : meta::size_as<Expr,2>
  {};

} }

#endif
