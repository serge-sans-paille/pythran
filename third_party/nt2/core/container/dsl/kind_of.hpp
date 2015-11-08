//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_KIND_OF_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_KIND_OF_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/proto/traits.hpp>

namespace nt2
{
  namespace tag { struct table_; }

  namespace ext
  {
    template<typename Tag, typename Domain, int Arity, typename Expr>
    struct kind_of
    {
      typedef tag::table_ type;
    };
  }

  namespace meta
  {
    template<typename Expr>
    struct  kind_of
          : ext::kind_of< typename boost::dispatch::meta::
                                           hierarchy_of < typename boost::proto
                                                          ::tag_of<Expr>::type
                                                        >::type
                                , typename boost::proto::domain_of<Expr>::type
                                , boost::proto::arity_of<Expr>::value
                                , Expr
                                >
    {};

    template<typename Expr>
    struct kind_of<Expr&> : kind_of<Expr> {};

    template<typename Expr>
    struct kind_of<Expr const> : kind_of<Expr> {};
  }
}

#include <nt2/core/container/dsl/details/kind/elementwise.hpp>

#endif
