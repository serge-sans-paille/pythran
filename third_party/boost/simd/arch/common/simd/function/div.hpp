//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIV_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIV_HPP_INCLUDED

#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/iceil.hpp>
#include <boost/simd/function/ifloor.hpp>
#include <boost/simd/function/ifix.hpp>
#include <boost/simd/function/iround.hpp>
#include <boost/simd/function/inearbyint.hpp>
#include <boost/simd/function/ceil.hpp>
#include <boost/simd/function/fix.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/round.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::ifix_
                          , bs::pack_<bd::floating_<T>, X>
                          , bs::pack_<bd::floating_<T>, X>
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<T> operator()( bd::functor<bs::tag::ifix_> const&
                                                    , T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return saturated_(toint)(a/b);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::iceil_
                          , bs::pack_<bd::floating_<T>, X>
                          , bs::pack_<bd::floating_<T>, X>
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<T> operator()( bd::functor<bs::tag::iceil_> const&
                                                    , T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return iceil(a/b);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::ifloor_
                          , bs::pack_<bd::floating_<T>, X>
                          , bs::pack_<bd::floating_<T>, X>
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<T> operator()( bd::functor<bs::tag::ifloor_> const&
                                                    ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return ifloor(a/b);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::iround_
                          , bs::pack_<bd::floating_<T>, X>
                          , bs::pack_<bd::floating_<T>, X>
                          )
  {
    BOOST_FORCEINLINE  bd::as_integer_t<T>  operator()( bd::functor<bs::tag::iround_> const&
                                                      ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return iround(a/b);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::inearbyint_
                          , bs::pack_<bd::floating_<T>, X>
                          , bs::pack_<bd::floating_<T>, X>
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

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::ifix_
                          , bs::pack_<bd::integer_<T>, X>
                          , bs::pack_<bd::integer_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::ifix_> const&
                                                    , T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return  div(fix, a, b);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::iceil_
                          , bs::pack_<bd::integer_<T>, X>
                          , bs::pack_<bd::integer_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::iceil_> const&
                                                    , T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return div(ceil, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::ifloor_
                          , bs::pack_<bd::integer_<T>, X>
                          , bs::pack_<bd::integer_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::ifloor_> const&
                                                    ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return  div(floor, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::iround_
                          , bs::pack_<bd::integer_<T>, X>
                          , bs::pack_<bd::integer_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::iround_> const&
                                                    ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return div(round, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::tag::inearbyint_
                          , bs::pack_<bd::integer_<T>, X>
                          , bs::pack_<bd::integer_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()( bd::functor<bs::tag::inearbyint_> const&
                                  ,T const& a, T const& b) const BOOST_NOEXCEPT
    {
      return  div(nearbyint, a, b);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( div_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<T>, X>
                          , bs::pack_<bd::arithmetic_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()(T const& a, T const& b ) const BOOST_NOEXCEPT
    {
      return divides(a, b);
    }
  };

} } }

#endif
