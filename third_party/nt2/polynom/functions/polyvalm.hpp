//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_POLYVALM_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_POLYVALM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief polyvalm generic tag

     Represents the polyvalm function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct polyvalm_ : ext::unspecified_<polyvalm_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<polyvalm_> parent;
    };
  }
  /*!
    computes the value of a polynomial p at a square matrix a using matricial product.
    the polynomial is supposed to be given by an array coefficients
    in decreasing degrees order

    @par Semantic:

    For every expression p representing and a representing a square matrix

    @code
    auto r = polyvalm(p, a);
    @endcode

    Computes \f$\displaystyle \sum_0^n p_i \mbox{mpow}(a, i)\f$.

    @see @funcref{mpower}
    @param a0

    @param a1

    @return an expression
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::polyvalm_, polyvalm, 2)

}

 namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::polyvalm_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<1>(e).extent();
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<tag::polyvalm_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }
#endif
