//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_REPVERT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_REPVERT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct repvert_ : ext::elementwise_<repvert_>
    {
      typedef ext::elementwise_<repvert_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::repvert_, repvert, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::repvert_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::repvert_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                ::child_c<Expr&,0>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      sizee[0] *= boost::proto::value(boost::proto::child_c<1>(e));
      return sizee;
    }
  };
} }

#endif
