//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RANDI_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RANDI_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag randi_ of functor randi
     **/
    struct randi_ : ext::unspecified_<randi_>
    {
      typedef ext::unspecified_<randi_>  parent;
    };
  }

  #define M0(z,n,t)                                                            \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::randi_, randi, n)                      \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::randi_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::randi_,Domain,N,Expr>
        : meta::boxed_size<Expr,2>
  {};
} }

#endif
