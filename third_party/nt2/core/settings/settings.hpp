//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_SETTINGS_HPP_INCLUDED
#define NT2_CORE_SETTINGS_SETTINGS_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/match_option.hpp>
#include <nt2/core/settings/forward/settings.hpp>

#include <boost/mpl/deref.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

//==============================================================================
/*!
 * Defines the maximum number of options that can be passed to a composite
 * settings. This macro can be set by users if needed.
 **/
//==============================================================================
#ifndef NT2_META_MAX_OPTIONS_NB
#define NT2_META_MAX_OPTIONS_NB 12
#endif

namespace nt2 { namespace meta
{
  //============================================================================
  // settings list of one argument return the argument option value
  //============================================================================
  template<class S0, class Option, class Semantic>
  struct  option< settings(S0), Option, Semantic >
        : option<S0,Option,Semantic>
  {};

  template< class S0, class Option>
  struct  match_option< settings(S0), Option >
        : match_option<S0,Option>
  {};

  //============================================================================
  // Non-empty settings lists are parse using mpl::find_if
  //============================================================================
  #define M0(z,n,t)                                                            \
  template< BOOST_PP_ENUM_PARAMS(n,class S), class Option>                     \
  struct  match_option< settings(BOOST_PP_ENUM_PARAMS(n,S)), Option >          \
        : boost::dispatch::meta::any< lambda_match_option<Option>              \
                                    , BOOST_PP_ENUM_PARAMS(n,S)                \
                                    >                                          \
  {};                                                                          \
                                                                               \
  template< BOOST_PP_ENUM_PARAMS(n,class S), class Option, class Semantic>     \
  struct option < settings(BOOST_PP_ENUM_PARAMS(n,S)), Option, Semantic >      \
  {                                                                            \
    typedef boost::mpl::vector##n<BOOST_PP_ENUM_PARAMS(n,S)>  options_t;       \
    typedef typename boost::mpl::find_if< options_t                            \
                                        , lambda_match_option<Option>          \
                                        >::type               it_t;            \
    typedef typename boost::mpl::deref<it_t>::type            found_t;         \
    typedef typename option<found_t,Option,Semantic>::type    type;            \
  };                                                                           \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,NT2_META_MAX_OPTIONS_NB,M0,~)

  #undef M0
} }

#endif
