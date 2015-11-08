//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_DSL_LAMBDA_GENERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_LAMBDA_GENERATOR_HPP_INCLUDED

#include <boost/proto/transform.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class Lambda>
  struct lambda_generator
    : proto::transform< lambda_generator<Lambda> >
  {
    template<class Expr, class State, class Data>
    struct impl : proto::transform_impl<Expr, State, Data>
    {
        typedef typename mpl::apply1<Lambda, typename boost::remove_const<typename impl::expr>::type>::type result_type;

        BOOST_FORCEINLINE
        result_type
        operator()( typename impl::expr_param e
                  , typename impl::state_param
                  , typename impl::data_param
                  ) const
        {
          return result_type(e);
        }
    };
  };

  template<class Lambda>
  struct lambda_pod_generator
    : proto::transform< lambda_pod_generator<Lambda> >
  {
    template<class Expr, class State, class Data>
    struct impl : proto::transform_impl<Expr, State, Data>
    {
        typedef typename mpl::apply1<Lambda, typename boost::remove_const<typename impl::expr>::type>::type result_type;

        BOOST_FORCEINLINE
        result_type
        operator()( typename impl::expr_param e
                  , typename impl::state_param
                  , typename impl::data_param
                  ) const
        {
          result_type const that = {e};
          return that;
        }
    };
  };
} } }

#endif
