#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_RESULT_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_RESULT_OF_HPP_INCLUDED

#include <boost/dispatch/details/parameters.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/utility/enable_if.hpp>
#if !defined(BOOST_NO_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
#include <boost/utility/declval.hpp>
#endif

#if (defined(BOOST_NO_VARIADIC_TEMPLATES) && defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)) || defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#endif

namespace boost { namespace dispatch
{
  namespace meta
  {
    #if !defined(BOOST_NO_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
    template<class Sig, class Enable = void>
    struct result_of_decltype {};
    #endif

    template<class Sig, class Enable = void>
    struct result_of
    #if !defined(BOOST_NO_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
         : result_of_decltype<Sig>
    #endif
    {};

    template<class T>
    struct is_function
      : boost::is_function<typename boost::remove_pointer<typename meta::strip<T>::type>::type>
    {
    };
  }
} }

#if (!defined(BOOST_NO_VARIADIC_TEMPLATES) && !defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)) || defined(DOXYGEN_ONLY)
namespace boost { namespace dispatch { namespace meta
{
#if !defined(BOOST_NO_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
  template<class F, class... Args>
  struct result_of_decltype<F(Args...), typename enable_if_type< decltype( boost::declval<F>()(boost::declval<Args>()...) ) >::type>
  {
    typedef decltype( boost::declval<F>()(boost::declval<Args>()...) ) type;
  };
#endif

  template<class F, class... Args>
  struct result_of<F(Args...), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };

  template<class F, class... Args>
  struct result_of<F(Args...), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };

  template<class F, class... Args>
  struct result_of<F(Args...), typename enable_if_type< typename F::template result<F(Args...)>::type >::type>
  {
    typedef typename F::template result<F(Args...)>::type type;
  };

} } }
#else
namespace boost { namespace dispatch { namespace meta
{
#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/meta/preprocessed/result_of.hpp>
#if !defined(BOOST_NO_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
#include <boost/dispatch/meta/preprocessed/result_of_decltype.hpp>
#endif
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/result_of.hpp")
#endif

  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 0, BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY), "boost/dispatch/meta/result_of.hpp"))
  #include BOOST_PP_ITERATE()

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/result_of_decltype.hpp")
#endif

  #if !defined(BOOST_NO_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)
    #define M0(z, n, t) boost::declval<A##n>()
    #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 0, BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY), "boost/dispatch/meta/result_of.hpp"))
    #include BOOST_PP_ITERATE()
    #undef M0
  #endif

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
} } }
#endif
#endif
#else
#define n BOOST_PP_ITERATION()

#ifdef M0
  template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
  struct result_of_decltype<F(BOOST_PP_ENUM_PARAMS(n, A)), typename enable_if_type< decltype( boost::declval<F>()(BOOST_PP_ENUM(n, M0, ~)) ) >::type>
  {
    typedef decltype( boost::declval<F>()(BOOST_PP_ENUM(n, M0, ~)) ) type;
  };
#else
  template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
  struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };

  template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
  struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };

  template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
  struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename enable_if_type< typename F::template result<F(BOOST_PP_ENUM_PARAMS(n, A))>::type >::type>
  {
    typedef typename F::template result<F(BOOST_PP_ENUM_PARAMS(n, A))>::type type;
  };
#endif

#undef n
#endif
