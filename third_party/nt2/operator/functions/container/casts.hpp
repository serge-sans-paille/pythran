//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_CONTAINER_CASTS_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_CONTAINER_CASTS_HPP_INCLUDED

#include <nt2/operator/functions/casts.hpp>
#include <nt2/include/functions/toints.hpp>
#include <nt2/include/functions/touints.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/groups.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/saturate.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/is_signed.hpp>

namespace nt2 { namespace ext
{
  // complexify if necessary
  template<class Expr, class From, class To, class Enable = void>
  struct casts_complexify
  {
    typedef Expr result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return e;
    }
  };

  template<class Expr, class From, class To>
  struct casts_complexify<Expr, From, To, typename boost::enable_if_c< meta::is_complex<To>::value && !meta::is_complex<From>::value >::type>
  {
    typedef typename meta::call<tag::complexify_(Expr)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return nt2::complexify(e);
    }
  };

  // upgrade -- split recursively
  template<class Expr, class From, class To, class Enable = void>
  struct casts_upgrade
  {
    typedef typename meta::call<tag::split_(Expr)>::type as_split;
    typedef casts_upgrade<as_split const, typename as_split::value_type, To> rec;
    typedef typename rec::result_type result_type;

    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return rec()(nt2::split(e));
    }
  };

  template<class Expr, class From, class To>
  struct casts_upgrade<Expr, From, To, typename boost::enable_if_c< sizeof(typename meta::primitive_of<From>::type) >= sizeof(typename meta::primitive_of<To>::type) >::type>
  {
    typedef Expr result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return e;
    }
  };

  // downgrade -- group recursively
  template<class Expr, class From, class To, class Enable = void>
  struct casts_downgrade
  {
    typedef typename meta::call<tag::groups_(Expr)>::type as_group;
    typedef casts_downgrade<as_group const, typename as_group::value_type, To> rec;
    typedef typename rec::result_type result_type;

    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return rec()(nt2::groups(e));
    }
  };

  template<class Expr, class From, class To>
  struct casts_downgrade<Expr, From, To, typename boost::enable_if_c< sizeof(typename meta::primitive_of<From>::type) <= sizeof(typename meta::primitive_of<To>::type) >::type>
  {
    typedef Expr result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return e;
    }
  };

  // intfloat -- call tofloat, toint or nothing depending on case
  template<class Expr, class From, class To, class Enable = void>
  struct casts_intfloat
  {
    typedef Expr result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return e;
    }
  };

  template<class Expr, class From, class To>
  struct casts_intfloat<Expr, From, To, typename boost::enable_if_c< meta::is_integral<From>::value && meta::is_floating_point<To>::value >::type>
  {
    typedef typename meta::call<tag::tofloat_(Expr)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return nt2::tofloat(e);
    }
  };

  template<class Expr, class From, class To>
  struct casts_intfloat<Expr, From, To, typename boost::enable_if< boost::mpl::and_< meta::is_integral<To>, meta::is_signed<To> > >::type>
  {
    typedef typename meta::call<tag::toints_(Expr)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return nt2::toints(e);
    }
  };

  template<class Expr, class From, class To>
  struct casts_intfloat<Expr, From, To, typename boost::enable_if< boost::mpl::and_< meta::is_integral<To>, meta::is_unsigned<To> > >::type>
  {
    typedef typename meta::call<tag::touints_(Expr)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(typename boost::dispatch::meta::as_ref<Expr>::type e) const
    {
      return nt2::touints(e);
    }
  };

  // casts
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::casts_, tag::cpu_
                            , (A0)(To)
                            , ((ast_<A0, nt2::container::domain>))
                              (target_< scalar_< unspecified_<To> > >)
                            )
  {
    typedef typename To::type       to;

    typedef casts_upgrade<A0&, typename A0::value_type, to> upgrade;
    typedef casts_intfloat<typename upgrade::result_type, typename boost::remove_reference<typename upgrade::result_type>::type::value_type, to> type;
    typedef casts_downgrade<typename type::result_type, typename boost::remove_reference<typename type::result_type>::type::value_type, to> downgrade;
    typedef casts_complexify<typename downgrade::result_type, typename boost::remove_reference<typename downgrade::result_type>::type::value_type, to> complexify_;

    typedef typename complexify_::result_type result_type;

    result_type operator()(A0& a0, To const&) const
    {
      return complexify_()(downgrade()(type()(upgrade()(a0))));
    }
  };
} }

#endif
