//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/grammar.hpp>
#include <nt2/core/container/view/view.hpp>
#include <nt2/core/container/view/shared_view.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <nt2/memory/functions/assign.hpp>
#include <nt2/sdk/memory/container_ref.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <boost/proto/domain.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>

namespace nt2 { namespace meta
{
  /* Checks whether a tag T is an elementwise operation */
  template<typename T>
  struct is_elementwise
  {
    typedef char true_type;
    struct false_type { char dummy[2]; };

    template<typename X>
    static true_type call(ext::elementwise_<X> const&);
    static false_type call(...);

    typedef typename boost::dispatch::meta::hierarchy_of<T>::type Tag;
    static const bool value = sizeof(call(Tag())) == sizeof(true_type);
    typedef boost::mpl::bool_<value> type;
  };

  /* If T is an expression, do nothing; otherwise call as_child in the domain
   * with T as a reference */
  template<typename T, typename Domain, typename Dummy = void>
  struct as_child
  {
    typedef typename Domain::template as_child<T&>::result_type type;
    static BOOST_FORCEINLINE type call(T& t)
    {
      return typename Domain::template as_child<T&>()(t);
    }
  };

  template<typename T, typename Domain>
  struct as_child<T, Domain, typename T::proto_is_expr_>
  {
    typedef T type;
    static BOOST_FORCEINLINE T& call(T& t)
    {
      return t;
    }
  };
} }

namespace nt2 { namespace container
{
  /* Turn an expression into a view, i.e. convert all container terminals and table
   * to view/shared_view */
  template<typename Expr, typename T>
  struct as_view_impl_term
       : boost::remove_const<Expr>
  {
  };

  template<typename Expr, typename Kind, typename T, typename S>
  struct as_view_impl_term< Expr, memory::container<Kind, T, S>& >
  {
    typedef view<Kind, T, S> type;
  };

  template<typename Expr, typename Kind, typename T, typename S>
  struct as_view_impl_term< Expr, memory::container<Kind, T, S> const& >
  {
    typedef view<Kind, T const, S> type;
  };

  template<typename Expr, typename Kind, typename T, typename S>
  struct as_view_impl_term< Expr, memory::container_shared_ref<Kind, T, S,true> & >
  {
    typedef shared_view<Kind, T, S> type;
  };

  template<typename Expr, typename Kind, typename T, typename S>
  struct as_view_impl_term< Expr, memory::container_shared_ref<Kind, T, S, true> const& >
  {
    typedef shared_view<Kind, T, S> type;
  };

  template<typename T, typename Tag = typename T::proto_tag>
  struct as_view_impl
  {
    typedef typename boost::remove_const<T>::type type;
    static BOOST_FORCEINLINE T& call(T& t)
    {
      return t;
    }
  };

  template<typename T>
  struct as_view_impl<T, boost::proto::tag::terminal>
  {
    typedef typename as_view_impl_term<T, typename boost::proto::result_of::value<T&>::type>::type type;
    static BOOST_FORCEINLINE type call(T& t)
    {
      return type(t);
    }
  };

  template<typename T>
  BOOST_FORCEINLINE
  typename as_view_impl<T>::type as_view(T& t)
  {
    return as_view_impl<T>::call(t);
  }

  template<typename T>
  BOOST_FORCEINLINE
  typename as_view_impl<T const>::type as_view(T const& t)
  {
    return as_view_impl<T const>::call(t);
  }

  /* The nt2 container domain has special rules so that children are held by value,
   * non-elementwise operations get scheduled and
   * containers are held by reference or as a container_ref value */
  struct  domain
        : boost::proto::domain< container::generator_transform<domain>
                              , container::grammar
                              >
  {
    // Construct an expression from a non-expression
    // - by value unless manually called with a reference
    // - semantic is same as terminal value
    template<typename T, typename Dummy = void, typename Sema = void>
    struct as_child : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type term_t;
      typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<term_t> > expr_t;
      typedef expression<expr_t, typename boost::mpl::if_< boost::is_void<Sema>, typename boost::remove_const<T>::type, Sema >::type> result_type;
      BOOST_FORCEINLINE result_type operator()(typename boost::add_reference<T>::type t) const
      {
        return result_type(expr_t::make(t));
      }
    };

    template<typename T, bool B>
    struct as_child_elementwise;

    template<typename T>
    struct as_child_elementwise<T, true>
         : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type result_type;
      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return result_type(t);
      }
    };

    // Schedule non-elementwise expression, return terminal (shared owning container_ref)
    template<typename T>
    struct as_child_elementwise<T, false>
         : boost::proto::callable
    {
      typedef typename boost::dispatch::meta::semantic_of<T&>::type              semantic;
      typedef typename boost::dispatch::meta::terminal_of_shared<semantic>::type terminal;
      typedef as_child<terminal>                                                 terminal_expr;
      typedef meta::as_child<terminal, domain>                                   terminal_ref;
      typedef typename terminal_expr::result_type                                result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        terminal term = boost::dispatch::meta::terminal_of_shared<semantic>::make();
        nt2::run(nt2::assign(terminal_ref::call(term), t));
        return terminal_expr()(term);
      }
    };

    template<typename T, typename Tag, bool Schedule = boost::is_same<typename T::proto_domain, domain>::value>
    struct as_child_expr
         : as_child_elementwise<T, meta::is_elementwise<Tag>::value || !Schedule >
    {
    };

    // Scheduled terminals: converted to views
    template<typename T>
    struct as_child_expr<T, boost::proto::tag::terminal, true>
     : boost::proto::callable
    {
      typedef typename as_view_impl<T>::type result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return as_view_impl<T>::call(t);
      }
    };

    // Non-scheduled terminals: ensure tables are held by reference
    template<typename T>
    struct as_child_expr<T, boost::proto::tag::terminal, false>
     : boost::proto::callable
    {
      typedef typename boost::proto::result_of::value<T&>::value_type value_type;
      typedef typename boost::mpl::if_< boost::is_const<T>, typename boost::add_const<value_type>::type, value_type >::type type;
      typedef typename boost::mpl::if_c< meta::is_container<value_type>::value && !meta::is_container_ref<value_type>::value, typename boost::add_reference<type>::type, type >::type type_ref;
      typedef as_child<type_ref, void, typename boost::dispatch::meta::semantic_of<T&>::type> impl;
      typedef typename impl::result_type result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return impl()(boost::proto::value(t));
      }
    };

    template<typename T>
    struct as_child<T, typename T::proto_is_expr_>
         : as_child_expr<T, typename T::proto_tag> {};
  };
} }

namespace nt2 { namespace meta
{
  /* Turn an expression into an element-wise expression, schedule but do not turn terminals into views */
  template<typename T, typename Tag = typename T::proto_tag>
  struct as_elementwise
  {
    typedef typename container::domain::template as_child<T>::result_type type;
    static BOOST_FORCEINLINE type call(T& t)
    {
      return typename container::domain::template as_child<T>()(t);
    }
  };

  template<typename T>
  struct as_elementwise<T, boost::proto::tag::terminal>
  {
    typedef T& type;
    static BOOST_FORCEINLINE T& call(T& t)
    {
      return t;
    }
  };
} }

#endif
