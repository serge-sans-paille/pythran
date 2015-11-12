//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPAND_TO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPAND_TO_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/sdk/meta/value_as.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief expand_to generic tag

     Represents the expand_to function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct expand_to_ : ext::elementwise_<expand_to_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<expand_to_> parent;
    };
  }

  /*!
    Expands expression to a given size enabling singleton expansion

    @par semantic:

    expand_to(a,siz) is conceptually equivalent (for additive element
    types) to bsxfun(plus, a, zeros(siz))

    size(a) and @c siz must be such that for every involved dimension
    @c i size(a, i) == siz(i) or 1.

    Whenever a dimension of @c a or @c b is singleton (i.e equal to
    one), expand_to virtually replicates the array along that
    dimension to match the given dimension in siz.

    @param a0 expression to process
    @param a1 size to expand to
    @return an expression which eventually will evaluate to the result
  **/

  #define M0(z,n,t)                                                           \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::expand_to_, expand_to, n)             \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)
  #undef M0
}
namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr,int N>
  struct  size_of<nt2::tag::expand_to_,Domain,N,Expr>
        : meta::boxed_size<Expr,1>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr, int N>
  struct  value_type<nt2::tag::expand_to_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
