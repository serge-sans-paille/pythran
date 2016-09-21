//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ELSE_HPP_INCLUDED

#ifdef BOOST_SIMD_BRANCH_FREE_IF_ELSE
#include <boost/simd/function/bitwise_select.hpp>
#include <boost/simd/function/genmask.hpp>
#endif
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( if_else_
                          , (typename COND, typename T, typename F)
                          , bd::cpu_
                          , bd::scalar_<bd::fundamental_<COND>>
                          , bd::scalar_<bd::fundamental_<T>>
                          , bd::scalar_<bd::fundamental_<F>>
                          )
  {
    BOOST_FORCEINLINE T operator()( COND cond
                                  , T t
                                  , F  f
                                  ) const BOOST_NOEXCEPT
    {
    #ifdef BOOST_SIMD_BRANCH_FREE_IF_ELSE
      return bitwise_select(genmask(cond), t, f);
    #else
      return cond ? t : T(f);
    #endif
    }
  };

    BOOST_DISPATCH_OVERLOAD ( if_else_
                          , (typename COND, typename T, typename F)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<COND>>
                          , bd::scalar_<bd::fundamental_<T>>
                          , bd::scalar_<bd::fundamental_<F>>
                          )
  {
    BOOST_FORCEINLINE T operator()( COND cond
                                  , T t
                                  , F  f
                                  ) const BOOST_NOEXCEPT
    {
    #ifdef BOOST_SIMD_BRANCH_FREE_IF_ELSE
      return bitwise_select(genmask(cond), t, f);
    #else
      return cond ? t : T(f);
    #endif
    }
  };
} } }


#endif
