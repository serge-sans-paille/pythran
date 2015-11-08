//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RAND_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/generative.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag rand_ of functor rand
     **/
    struct rand_ : ext::unspecified_<rand_>
    {
      typedef ext::unspecified_<rand_>  parent;
    };
  }

  #define M0(z,n,t)                                     \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::rand_, rand, n) \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::rand_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type        c_t;
    typedef typename boost::proto::result_of::value<c_t>::value_type::type  type;
  };

  template<class Domain, class Expr, int N>
  struct  size_of<tag::rand_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
