//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_ADD_SETTINGS_HPP_INCLUDED
#define NT2_CORE_SETTINGS_ADD_SETTINGS_HPP_INCLUDED

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/proto/expr.hpp>

namespace nt2 { namespace meta
{
  /*!
    @brief

    @tparam Original
    @tparam New
  **/
  template<typename Original, typename New = void>
  struct add_settings
  {
    typedef nt2::settings type(New,Original);
  };

  /// INTERNAL ONLY
  template<typename Original, typename New>
  struct add_settings<Original&, New>
  {
    typedef typename add_settings<Original,New>::type& type;
  };

  /// INTERNAL ONLY
  template<typename Original, typename New>
  struct add_settings<Original const, New>
  {
    typedef typename add_settings<Original,New>::type const type;
  };

  /// INTERNAL ONLY
  template<typename Original>
  struct add_settings<Original,void>
  {
    typedef Original type;
  };

  /// INTERNAL ONLY
  template<typename Original>
  struct add_settings<Original, nt2::settings()>
  {
    typedef Original type;
  };

  /// INTERNAL ONLY
  template<>
  struct add_settings<nt2::settings()>
  {
    typedef nt2::settings type();
  };

  /// INTERNAL ONLY
  template<>
  struct add_settings<nt2::settings(),nt2::settings()>
  {
    typedef nt2::settings type();
  };

  /// INTERNAL ONLY
  template<typename New>
  struct add_settings<nt2::settings(), New>
  {
    typedef New type;
  };

  /// INTERNAL ONLY
  template<typename S0, typename S1>
  struct add_settings<nt2::settings(S0), nt2::settings(S1)>
  {
    typedef nt2::settings type(S1,S0);
  };

  /// INTERNAL ONLY
  template<typename Original>
  struct add_settings<nt2::settings(Original), void>
  {
    typedef Original type;
  };

  /// INTERNAL ONLY
  #define M0(z,n,t)                                                            \
  template<typename Original, BOOST_PP_ENUM_PARAMS(n,typename New)>            \
  struct add_settings< Original, settings(BOOST_PP_ENUM_PARAMS(n,New))>        \
  {                                                                            \
    typedef nt2::settings type(BOOST_PP_ENUM_PARAMS(n,New),Original);          \
  };                                                                           \
  template<typename Original, BOOST_PP_ENUM_PARAMS(n,typename New)>            \
  struct add_settings < settings(Original)                                     \
                      , settings(BOOST_PP_ENUM_PARAMS(n,New))>                 \
  {                                                                            \
    typedef nt2::settings type(BOOST_PP_ENUM_PARAMS(n,New),Original);          \
  };                                                                           \
  /**/

  /// INTERNAL ONLY
  BOOST_PP_REPEAT_FROM_TO(2,NT2_META_MAX_OPTIONS_NB,M0,~)

  #undef M0

  /// INTERNAL ONLY
  template<typename Original, typename New>
  struct add_settings < boost::proto::basic_expr< boost::proto::tag::terminal
                                                , boost::proto::term<Original>
                                                , 0l
                                                >
                      , New
                      >
  {
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto
                                           ::term < typename  add_settings
                                                              < Original
                                                              , New
                                                              >::type
                                                  >
                                    , 0l
                                    >                               type;
  };

  /// INTERNAL ONLY
  template<typename Expr, typename Semantic, typename New>
  struct add_settings< nt2::container::expression<Expr, Semantic>, New >
  {
    typedef nt2::container::expression< typename add_settings<Expr, New>::type
                                      , typename add_settings<Semantic, New>::type
                                      >                             type;
  };
} }

#endif
