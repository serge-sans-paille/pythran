//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_AS_TERMINAL_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_AS_TERMINAL_HPP_INCLUDED

#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace nt2 { namespace meta
{
  template<class Value>
  struct is_container_shared
       : boost::mpl::false_
  {
  };

  template<typename Kind, typename T, typename S, bool Own>
  struct is_container_shared< memory::container_shared_ref<Kind, T, S, Own> >
       : boost::mpl::true_
  {
  };

  template<class In, long Arity = boost::remove_reference<In>::type::proto_arity_c>
  struct is_terminal_shared
       : boost::mpl::false_
  {
  };

  template<class In>
  struct is_terminal_shared<In, 0>
       : is_container_shared<typename boost::remove_reference<In>::type::proto_child0>
  {
  };
} }

namespace nt2 { namespace container
{
  template<class Semantic, class Expr = int, class Enable = void>
  struct as_terminal
       : boost::dispatch::meta::terminal_of<Semantic>
  {
    static typename as_terminal::type init(Expr)
    {
      return typename as_terminal::type();
    }
  };

  // TODO: check interleaving and storage order is same
  template<class Semantic, class Expr>
  struct as_terminal< Semantic
                    , Expr
                    , typename boost::
                      enable_if_c< boost::remove_reference<Expr>::type::proto_arity_c == 0
                                && boost::is_same< typename boost::remove_reference<Expr>::type::value_type
                                                 , typename Semantic::value_type >::value
                                                 >::type
                    >
  {
    typedef Expr type;
    static type init(Expr expr)
    {
      return expr;
    }
  };

  template<class Semantic, class In, class Out, class Enable = void>
  struct as_terminal_inout
  {
    typedef as_terminal<Semantic, Out> impl;
    typedef typename impl::type type;

    static type init(In in, Out out)
    {
      type result = impl::init(out);
      result = in;
      return result;
    }
  };

  template<class Semantic, class In, class Out>
  struct as_terminal_inout< Semantic, In, Out
                          , typename boost::enable_if< meta::is_terminal_shared<In> >::type
                        >
  {
    typedef In type;

    static type init(In in, Out)
    {
      return in;
    }
  };
} }

#define NT2_AS_TERMINAL_IN(semantic, name, input) typename container::as_terminal<semantic, BOOST_DISPATCH_DECLTYPE((input))>::type name = (input);
#define NT2_AS_TERMINAL_OUT(semantic, name, output) typename container::as_terminal<semantic, BOOST_DISPATCH_DECLTYPE((output))>::type name = container::as_terminal<semantic, BOOST_DISPATCH_DECLTYPE((output))>::init((output));
#define NT2_AS_TERMINAL_INOUT(semantic, name, input, output) typename container::as_terminal_inout<semantic, BOOST_DISPATCH_DECLTYPE((input)), BOOST_DISPATCH_DECLTYPE((output))>::type name = container::as_terminal_inout<semantic, BOOST_DISPATCH_DECLTYPE((input)), BOOST_DISPATCH_DECLTYPE((output))>::init((input), (output));

#endif
