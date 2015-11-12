//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_DOMAIN_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_DOMAIN_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/proto/domain.hpp>
#include <boost/proto/traits.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Tell proto that in the simd::domain, all expressions should be
  // wrapped in simd::expr<> using simd::generator
  ////////////////////////////////////////////////////////////////////////////
  struct domain : boost::proto::domain< generator
                                      , grammar
                                      >
  {
    template<class T, class Dummy = void>
    struct as_child : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type term_t;
      typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<term_t> > expr_t;
      typedef expression<expr_t, typename boost::dispatch::meta::semantic_of<term_t>::type> result_type;
      BOOST_FORCEINLINE result_type operator()(typename boost::add_reference<T>::type t) const
      {
        result_type that = { expr_t::make(t) };
        return that;
      }
    };

    template<class T, class Tag>
    struct as_child_expr : boost::proto::callable
    {
      typedef typename boost::remove_const<T>::type result_type;
      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return result_type(t);
      }
    };

    template<class T>
    struct as_child_expr<T, boost::proto::tag::terminal>
     : boost::proto::callable
    {
      typedef typename boost::proto::result_of::value<T&>::value_type value_type;
      typedef typename boost::mpl::if_< boost::is_const<T>, typename boost::add_const<value_type>::type, value_type >::type type;
      typedef typename boost::mpl::if_< meta::is_native<value_type>, typename boost::add_reference<type>::type, type >::type term;

      typedef as_child<term> impl;
      typedef typename impl::result_type result_type;

      BOOST_FORCEINLINE result_type operator()(T& t) const
      {
        return impl()(boost::proto::value(t));
      }
    };

    template<class T>
    struct as_child<T, typename T::proto_is_expr_>
         : as_child_expr<T, typename T::proto_tag> {};
  };
} }

#endif
