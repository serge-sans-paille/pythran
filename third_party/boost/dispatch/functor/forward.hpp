//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_FORWARD_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_FORWARD_HPP_INCLUDED

#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/dispatch/meta/counter.hpp>
#include <boost/dispatch/meta/combine.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/config.hpp>

BOOST_DISPATCH_COUNTER_INIT(default_site_stack)

namespace boost { namespace dispatch
{
  template<class Tag, int N>
  struct default_site_impl;

  template<class Tag>
  struct default_site_impl<Tag, 0>
  {
    typedef tag::cpu_ type;
  };

  //============================================================================
  /*
   * default_site defines the architecture dependent default evaluation context
   * for functors.
   */
  //============================================================================
#ifndef BOOST_MSVC
  using meta::default_site_stack;
#endif
  template<class Tag>
  struct default_site
  {
    static const int value = BOOST_DISPATCH_COUNTER_VALUE_TPL(default_site_stack, Tag);
    typedef typename default_site_impl<Tag, value>::type type;
  };

  template< class Tag
          , class EvalContext = typename default_site<Tag>::type
          >
  struct functor;
} }

namespace boost { namespace dispatch { namespace meta
{
  template< class Signature , class Site, class Dummy = void> struct implement;
  template< class Tag> struct proto_tag;
} } }


#ifdef BOOST_MSVC
#define BOOST_DISPATCH_COMBINE_SITE(new_site) BOOST_DISPATCH_COMBINE_SITE_(new_site, __COUNTER__)

#define BOOST_DISPATCH_COMBINE_SITE_(new_site, N)                                                  \
namespace boost { namespace dispatch                                                               \
{                                                                                                  \
  static const int BOOST_PP_CAT(default_site_stack_value_,  N)                                     \
    = BOOST_DISPATCH_COUNTER_VALUE(default_site_stack);                                            \
  template<class Tag>                                                                              \
  struct default_site_impl<Tag, BOOST_PP_CAT(default_site_stack_value_,  N) + 1>                   \
   : meta::combine< typename default_site_impl< Tag                                                \
                                              , BOOST_PP_CAT(default_site_stack_value_,  N)        \
                                              >::type                                              \
                  , BOOST_DISPATCH_PP_STRIP(new_site)                                              \
                  >                                                                                \
  {                                                                                                \
  };                                                                                               \
} }                                                                                                \
BOOST_DISPATCH_COUNTER_INCREMENT(default_site_stack)                                               \
/**/
#else
#define BOOST_DISPATCH_COMBINE_SITE(new_site)                                                      \
namespace boost { namespace dispatch                                                               \
{                                                                                                  \
  template<class Tag>                                                                              \
  struct default_site_impl<Tag, BOOST_DISPATCH_COUNTER_VALUE(default_site_stack) + 1>              \
   : meta::combine< typename default_site_impl< Tag                                                \
                                              , BOOST_DISPATCH_COUNTER_VALUE(default_site_stack)   \
                                              >::type                                              \
                  , BOOST_DISPATCH_PP_STRIP(new_site)                                              \
                  >                                                                                \
  {                                                                                                \
  };                                                                                               \
} }                                                                                                \
BOOST_DISPATCH_COUNTER_INCREMENT(default_site_stack)                                               \
/**/
#endif

#define BOOST_DISPATCH_DEFAULT_SITE_FOR(Tag)                                                       \
namespace boost { namespace dispatch                                                               \
{                                                                                                  \
  template<>                                                                                       \
  struct default_site<BOOST_DISPATCH_PP_STRIP(Tag)>                                                \
    : default_site_impl<BOOST_DISPATCH_PP_STRIP(Tag), 0>                                           \
  {                                                                                                \
  };                                                                                               \
} }                                                                                                \
/**/

#endif
