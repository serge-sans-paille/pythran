//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_DIV_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_DIV_HPP_INCLUDED

#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/definition/fix.hpp>
#include <boost/simd/function/ifloor.hpp>
#include <boost/simd/function/ifix.hpp>
#include <boost/simd/function/iround.hpp>
#include <boost/simd/function/inearbyint.hpp>
#include <boost/simd/arch/common/scalar/function/divceil.hpp>
#include <boost/simd/arch/common/scalar/function/divfloor.hpp>
#include <boost/simd/arch/common/scalar/function/divround.hpp>
#include <boost/simd/arch/common/scalar/function/divnearbyint.hpp>
#include <boost/simd/arch/common/scalar/function/divtrunc.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{

  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::arithmetic_<T>>
                          , bd::scalar_<bd::arithmetic_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T  a, T  b ) const BOOST_NOEXCEPT
    {
      return divides(a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::fix_
                          , bd::scalar_<bd::arithmetic_<T>>
                          , bd::scalar_<bd::arithmetic_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::fix_> const&
                                  , T  a, T  b ) const BOOST_NOEXCEPT
    {
      return div(bs::trunc, a, b);
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::ifix_
                          , bd::scalar_<bd::floating_<T>>
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<T> operator()( bd::functor<bs::tag::ifix_> const&
                                                    , T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return saturated_(toint)(a/b);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::iceil_
                          , bd::scalar_<bd::floating_<T>>
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<T> operator()( bd::functor<bs::tag::iceil_> const&
                                                    , T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return iceil(a/b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::ifloor_
                          , bd::scalar_<bd::floating_<T>>
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<T> operator()( bd::functor<bs::tag::ifloor_> const&
                                                    ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return ifloor(a/b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::iround_
                          , bd::scalar_<bd::floating_<T>>
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE  bd::as_integer_t<T>  operator()( bd::functor<bs::tag::iround_> const&
                                                      ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return iround(a/b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::inearbyint_
                          , bd::scalar_<bd::floating_<T>>
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<T> operator()( bd::functor<bs::tag::inearbyint_> const&
                                                    ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return pedantic_(inearbyint)(a/b);
    }
  };

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::ifix_
                          , bd::scalar_<bd::integer_<T>>
                          , bd::scalar_<bd::integer_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::ifix_> const&
                                                    , T  a, T  b ) const BOOST_NOEXCEPT
    {
      return  div(fix, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::iceil_
                          , bd::scalar_<bd::integer_<T>>
                          , bd::scalar_<bd::integer_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::iceil_> const&
                                                    , T  a, T  b ) const BOOST_NOEXCEPT
    {
      return div(ceil, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::ifloor_
                          , bd::scalar_<bd::integer_<T>>
                          , bd::scalar_<bd::integer_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::ifloor_> const&
                                                    ,T  a, T  b) const BOOST_NOEXCEPT
    {
      return  div(floor, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::iround_
                          , bd::scalar_<bd::integer_<T>>
                          , bd::scalar_<bd::integer_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::iround_> const&
                                                    ,T  a, T  b) const BOOST_NOEXCEPT
    {
      return div(round, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( div_
                          , (typename T)
                          , bd::cpu_
                          , bs::tag::inearbyint_
                          , bd::scalar_<bd::integer_<T>>
                          , bd::scalar_<bd::integer_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::inearbyint_> const&
                                  ,T  a, T  b) const BOOST_NOEXCEPT
    {
      return  div(nearbyint, a, b);
    }
  };


} } }

#endif
