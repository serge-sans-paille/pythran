//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_EVAL_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_EVAL_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

/*
  Various forward declarations
*/
namespace boost { namespace simd
{
  template<class T, class X>
  struct soa_proxy;

  template<class Expr, class ResultType>
  struct expression;
} }

namespace nt2
{
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  struct of_size_;
}

namespace nt2
{
  namespace container
  {
    template<class Expr, class Result>
    struct expression;
  }

  namespace unit
  {
    template<class T>
    BOOST_FORCEINLINE T const& eval(T const& t)
    {
      return t;
    }

    template<class Expr, class Result>
    typename boost::dispatch::meta::terminal_of<Result>::type
    eval(nt2::container::expression<Expr, Result> const& t)
    {
      return t;
    }

    template<class Expr, class Result>
    typename boost::dispatch::meta::terminal_of<Result>::type
    eval(boost::simd::expression<Expr, Result> const& t)
    {
      return t;
    }

    template<class T, class X>
    T eval(boost::simd::soa_proxy<T, X> const& t)
    {
      return t;
    }

    template<typename T, std::ptrdiff_t D> struct make_dependent_c
    {
      typedef T type;

    };
    // Add specialization for of_size_
    template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
    BOOST_FORCEINLINE typename
    make_dependent_c< of_size_<  BOOST_PP_ENUM_PARAMS ( NT2_MAX_DIMENSIONS
                                                      , std::ptrdiff_t(-1) BOOST_PP_INTERCEPT
                                                      )
                              >
                    , D0
                    >::type
    eval(of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)> const& t)
    {
      return t;
    }
  }
}

#endif
