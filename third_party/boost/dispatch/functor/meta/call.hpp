#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_META_CALL_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_META_CALL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the \ref boost::dispatch::meta::call \metafunction
 */

#include <boost/config.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/meta/result_of.hpp>
#include <boost/dispatch/meta/as_ref.hpp>

#if (defined(BOOST_NO_VARIADIC_TEMPLATES) && defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)) || defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#endif

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * \ref call is a \metafunction that, for a given \c Tag, \c EvalContext and
   * argument lists \c ...Args, computes the return type of
   * functor<Tag,EvalContext>::operator()(Args...).
   *
   * \param Sig         function type build from Tag(Args...)
   * \param EvalContext evaluation context to use for type deduction
   *
   * \par Models:
   * \metafunction
   *
   * \par Semantics:
   * For a given \c Tag, \c EvalContext and argument lists \c ...Args,
   *
   * \code
   * typedef call<Tag(Args...),EvalContext>::type type;
   * \endcode
   *
   * is equivalent to:
   * \code
   * typedef decltype(functor<Tag,EvalContext>(declval<Args...>())) type;
   * \endcode
   */
  //============================================================================
  template< class Sig
          , class EvalContext = void
          > struct call {};

#if (!defined(BOOST_NO_VARIADIC_TEMPLATES) && !defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)) || defined(DOXYGEN_ONLY)
  template<class Tag, class... Args, class Site>
  struct  call<Tag(Args...),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(typename meta::as_ref<Args>::type...), Site>::type(Args...)>
  {
  };
#else

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/functor/meta/preprocessed/call.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call.hpp")
#endif

  #define M0(z,n,t) typename meta::as_ref<A##n>::type

  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_DISPATCH_MAX_ARITY, "boost/dispatch/functor/meta/call.hpp"))
  #include BOOST_PP_ITERATE()

  #undef M0

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
#endif

} } }

#endif

#else /* BOOST_PP_IS_ITERATING */
#define n BOOST_PP_ITERATION()

  template<class Tag, BOOST_PP_ENUM_PARAMS(n,class A), class Site>
  struct  call<Tag(BOOST_PP_ENUM_PARAMS(n,A)),Site>
        : meta::result_of<typename meta::dispatch_call<Tag(BOOST_PP_ENUM(n,M0,~)), Site>::type(BOOST_PP_ENUM_PARAMS(n,A))>
  {
  };

#undef n
#endif

