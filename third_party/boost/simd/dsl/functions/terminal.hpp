//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_TERMINAL_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_TERMINAL_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/function.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct terminal_    : ext::elementwise_<terminal_> { typedef ext::elementwise_<terminal_> parent; };
    struct dereference_ : terminal_{ typedef terminal_ parent; };
  }

  template<class Expr>
  BOOST_FORCEINLINE typename boost::dispatch::meta::call<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type(Expr const&)>::type
  terminal(Expr const& e)
  {
    return boost::dispatch::functor<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type>()(e);
  }

  template<class Expr>
  BOOST_FORCEINLINE typename boost::dispatch::meta::call<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type(Expr&)>::type
  terminal(Expr& e)
  {
    return boost::dispatch::functor<typename boost::dispatch::meta::hierarchy_of<typename Expr::proto_tag>::type>()(e);
  }
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::terminal>
  {
    typedef boost::simd::tag::terminal_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::terminal_>
  {
    typedef boost::proto::tag::terminal type;
  };
  template<>
  struct is_formal<boost::simd::tag::terminal_>
   : mpl::true_
  {
  };

  template<>
  struct hierarchy_of<boost::proto::tag::dereference>
  {
    typedef boost::simd::tag::dereference_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::dereference_>
  {
    typedef boost::proto::tag::dereference type;
  };
} } }

#endif
