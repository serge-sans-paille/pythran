#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED

#include <boost/dispatch/details/typeof.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/functor/details/call.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_void.hpp>

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/functor/details/preprocessed/dispatch.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/dispatch.hpp")
#undef BOOST_DISPATCH_TYPEOF_
#undef BOOST_FORCEINLINE
#endif

#define M0(z,n,t) , meta::unknown_<A##n>
#define M1(z,n,t) , (typename meta::hierarchy_of<A##n>::type())

namespace boost { namespace dispatch { namespace meta
{
  struct adl_helper {};

  //==============================================================================
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //==============================================================================
  template<class Sig, class Site = void>
  struct dispatch_call;

  //==============================================================================
  // What the fuck with adl_helper ? Well, as pointed out by Johannes Schaub
  // it is mandated by the standard so ADL kicks in on resolving calls to
  // dispatching without having to order them BEFORE the actual dispatch_call
  // class definitions. Without it, the whole system brittles.
  //==============================================================================
  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 0, BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY), "boost/dispatch/functor/details/dispatch.hpp"))
  #include BOOST_PP_ITERATE()

} } }

#undef M1
#undef M0

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
#endif

#else /* BOOST_PP_IS_ITERATING */
#define n BOOST_PP_ITERATION()

  template< class Tag, class Site
          BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,class A)
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(BOOST_PP_ENUM_PARAMS(n, A))>
  dispatching ( meta::unknown_<Tag>, meta::unknown_<Site>
              BOOST_PP_REPEAT(n,M0,~)
              , adl_helper = adl_helper()
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(BOOST_PP_ENUM_PARAMS(n, A))
                                    > that;
    return that;
  }

  template< class Tag, class Site_
          BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,class A)
          >
  struct dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n,A)), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;

    BOOST_DISPATCH_TYPEOF_
    ( dispatching ( (typename meta::hierarchy_of<Tag>::type())
                  , (typename meta::hierarchy_of<Site>::type())
                  BOOST_PP_REPEAT(n,M1,~)
                  , adl_helper()
                  )
    , type
    )
  };

#undef n
#endif
