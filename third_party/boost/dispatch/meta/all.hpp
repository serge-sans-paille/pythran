//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_ALL_HPP_INCLUDED
#define BOOST_DISPATCH_META_ALL_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::all @metafunction.
 **/

#include <boost/config.hpp>
#include <boost/dispatch/meta/na.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#endif

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Recursive variadics
  //============================================================================
#if defined(DOXYGEN_ONLY)
  /*!
   * @brief
   * Evaluates if a given meta-predicate is true for all types in a type
   * sequence. @c all works with classic enumeration of template parameters,
   * while @c all_seq works on a @metasequence.
   *
   * @tparam Pred Boolean @metafunction
   * @tparam Args List of types to assert
   *
   * @par Models:
   *
   * @metafunction
   *
   * @par Semantic:
   *
   * For any types @c Pred and @c T0,...,Tn
   *
   * @code
   * typedef all<Pred,T0,...,Tn>::type type;
   * @endcode
   *
   * Returns @true_ if, for all types @c T in @c T0,...,Tn,
   * @c apply1<Pred,T>::type is @true_. Otherwise, returns @false_.
   *
   * @par Usage:
   *
   * @include all.cpp
   **/
  template< class Pred, class... Args>
  struct all;
#elif defined(BOOST_HAS_VARIADIC_TMPL)
   //============================================================================
  // Recursive variadic version
  //============================================================================
  template< class Predicate, class... Args>
  struct all : boost::mpl::true_ {};

  template< class Pred, class Head, class... Tails>
  struct  all<Pred,Head,Tails...>
        : boost::mpl::and_< boost::mpl::apply1<Pred,Head>
                          , all<Pred,Tails...>
                          >
  {};
#else
  //============================================================================
  // Macro based version
  //============================================================================
  #define M1(z,n,t)                                                            \
  BOOST_PP_EXPR_IF(n, &&) boost::mpl::apply1<Pred,BOOST_PP_CAT(A,n)>::type::value \
  /**/

  template< class Pred
          , BOOST_PP_ENUM_BINARY_PARAMS ( BOOST_DISPATCH_MAX_META_ARITY
                                        , class A
                                        , = dispatch::meta::na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct  all;

  #define M0(z,n,t)                                                           \
  template<class Pred, BOOST_PP_ENUM_PARAMS(n,class A)>                       \
  struct  all<Pred,BOOST_PP_ENUM_PARAMS(n,A)>                                 \
        : boost::mpl::bool_<BOOST_PP_REPEAT(n,M1,~)>                          \
  {};                                                                         \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_META_ARITY,M0,~)

  #undef M1
  #undef M0

#endif

  template< class Pred, class T>
  struct  all_seq
        : boost::is_same< typename boost::mpl::find_if<T, boost::mpl::not_<Pred> >::type
                        , typename boost::mpl::end<T>::type
                        >
  {};

} } }

#endif
