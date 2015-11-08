//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_SPECIFIC_UTILS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_SPECIFIC_UTILS_HPP_INCLUDED

#include <boost/simd/sdk/meta/cardinal_as.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/na.hpp>

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

namespace boost { namespace simd { namespace ext
{
  #define BOOST_DISPATCH_FOLD_0(z,n,t) BOOST_PP_COMMA_IF(n) BOOST_PP_TUPLE_ELEM(4, 0, t) BOOST_PP_TUPLE_ELEM(4, 2, t)(z,n,BOOST_PP_TUPLE_ELEM(4, 3, t))
  #define BOOST_DISPATCH_FOLD_1(z,n,t) t
  #define BOOST_DISPATCH_FOLD(n, prefix, postfix, m, d) BOOST_PP_REPEAT(BOOST_PP_DEC(n), BOOST_DISPATCH_FOLD_0, (prefix, postfix, m, d)) BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) m(BOOST_PP_DEC(n),BOOST_PP_DEC(n),d) BOOST_PP_REPEAT(BOOST_PP_DEC(n), BOOST_DISPATCH_FOLD_1, postfix)

  template<std::size_t N, std::size_t M>
  struct cardinal_common;

  template<>
  struct cardinal_common<1, 1>
  {
    static const std::size_t value = 1;
  };

  template<std::size_t N>
  struct cardinal_common<1, N>
  {
    static const std::size_t value = N;
  };

  template<std::size_t N>
  struct cardinal_common<N, 1>
  {
    static const std::size_t value = N;
  };

  template<std::size_t N>
  struct cardinal_common<N, N>
  {
    static const std::size_t value = N;
  };

  template<class T, class U>
  struct ext_common
  {
    typedef dispatch::meta::na_ type;
  };

  template<class T>
  struct ext_common<dispatch::meta::na_, T>
  {
    typedef T type;
  };

  template<class T>
  struct ext_common<T, dispatch::meta::na_>
  {
    typedef T type;
  };

  template<>
  struct ext_common<dispatch::meta::na_, dispatch::meta::na_>
  {
    typedef dispatch::meta::na_ type;
  };

  template<class T>
  struct ext_common<T, T>
  {
    typedef T type;
  };


  template<class T, std::size_t N, class X, int Cmp = (!(meta::cardinal_as<T, X>::value >= N) ? -1 : !(meta::cardinal_as<T, X>::value <= N) ? 1 : 0) >
  struct vector_on_ext;

  template<class T, std::size_t N, class X>
  struct vector_on_ext<T, N, X, 0>
  {
    typedef native<T, X> type;
  };

  template<class T, std::size_t N, class X>
  struct vector_on_ext<T, N, X, -1>
       : vector_on_ext<typename dispatch::meta::downgrade<T>::type, N, X>
  {
  };

  template<class T, std::size_t N>
  struct vector_on_ext<T, N, dispatch::meta::na_, -1>
  {
    typedef T type;
  };

  template<class T, std::size_t N, class X>
  struct vector_on_ext<T, N, X, 1>
       : vector_on_ext<typename dispatch::meta::upgrade<T>::type, N, X>
  {
  };
} } }

#endif
