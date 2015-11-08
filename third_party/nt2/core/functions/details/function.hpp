//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_FUNCTION_HPP_INCLUDED

#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/details/resize.hpp>
#include <nt2/core/container/dsl/details/generator.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/proto/traits.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<> struct hierarchy_of<boost::proto::tag::function>
  {
    typedef nt2::tag::function_ type;
  };

  template<> struct proto_tag<nt2::tag::function_>
  {
    typedef boost::proto::tag::function type;
  };
} } }


namespace nt2
{
  namespace tag
  {
    struct function_index_;
  }

  namespace ext
  {
    //============================================================================
    // resize function expression - do nothing
    //============================================================================
    template<class Domain, int N, class Expr>
    struct resize<nt2::tag::function_, Domain, N, Expr>
    {
      template<class Sz> BOOST_FORCEINLINE void operator()(Expr&, Sz const&) {}
    };

    //============================================================================
    // Extension of value_type to handle function call nodes
    // The returned value is the value_type of the leftmost children of the node
    //============================================================================
    template<class Expr, class Domain, int N>
    struct value_type<tag::function_, Domain, N, Expr>
    {
      typedef typename boost::proto::result_of::child_c<Expr&, 0>::type   child0;

      typedef typename boost::dispatch::meta::
              scalar_of < typename boost::dispatch::meta::
                          semantic_of<child0>::type
                        >::type                                           type;
    };

    //============================================================================
    // Size of a function call node depends of the indexers
    //============================================================================
    template<class Expr, class Domain, int N>
    struct size_of<tag::function_, Domain, N, Expr>
    {
      typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type child1;
      typedef size_of<tag::function_index_, Domain, N, child1 const> impl;
      typedef typename impl::result_type result_type;

      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        return impl()(boost::proto::child_c<1>(e));
      }
    };

    //==========================================================================
    // Size_of nullary function call case - handle expr()
    //==========================================================================
    template<class Expr, class Domain>
    struct  size_of<tag::function_, Domain, 1, Expr>
          : meta::size_as<Expr,0> {};
  }

  namespace details
  {
    //==========================================================================
    // Generator nullary function call case - handle expr()
    //==========================================================================
    template<class Domain, class Expr>
    struct  generator<tag::function_, Domain, 1, Expr>
    {
      typedef typename boost::proto::result_of::child_c<Expr,0>::type   expr_t;
      typedef typename boost::dispatch::meta::semantic_of<expr_t>::type sema_t;

      typedef container::expression < typename boost::remove_const<Expr>::type
                                    , sema_t
                                    >                               result_type;

      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        return result_type(e);
      }
    };
  }
}

#endif
