//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DELTAC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DELTAC_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

/*
In mathematics, the Kronecker delta or Kronecker's delta, named after Leopold Kronecker, is a function of two variables, usually integers.
The function is 1 if the variables are equal, and 0 otherwise:
\delta_{ij} = \begin{cases}
0 &\text{if } i \neq j   \\
1 &\text{if } i=j,   \end{cases}
*/

namespace nt2
{
  namespace tag
  {
    /*!
      @brief deltac generic tag

      Represents the deltac function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct deltac_ : ext::state_constant_<deltac_>
    {
      /// @brief Parent hierarchy
      typedef ext::state_constant_<deltac_> parent;

      /// @brief default value type for untyped calls
      typedef double                      default_type;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::deltac_, deltac, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::deltac_, deltac, 4)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::deltac_, deltac, 5)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::deltac_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::deltac_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
