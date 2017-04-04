//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_CONSTANT_CONSTANT_GENERATOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_CONSTANT_CONSTANT_GENERATOR_HPP_INCLUDED

#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // Truncation
#pragma warning(disable: 4309) // Truncation
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  BOOST_DISPATCH_OVERLOAD_FALLBACK( (typename X, typename V)
                                  , boost::dispatch::constant_value_<tag::constant_>
                                  , boost::dispatch::cpu_
                                  , bd::scalar_<bd::unspecified_<V>>
                                  , bd::target_< bd::unspecified_<X> >
                                  )
  {
    template<typename T, T N>
    static BOOST_FORCEINLINE T impl(tt::integral_constant<T,N> const&) BOOST_NOEXCEPT
    {
      return tt::integral_constant<T,N>{};
    }

    template<typename R, typename T, T N>
    static BOOST_FORCEINLINE R impl(nsm::real_<R,T,N> const& ) BOOST_NOEXCEPT
    {
      return static_cast<R>(nsm::real_<R,T,N>{});
    }

    template<typename T, std::intmax_t N, std::intmax_t D>
    static BOOST_FORCEINLINE T impl(detail::ratio<T,N,D> const&) BOOST_NOEXCEPT
    {
      return T(double(N)/double(D));
    }

    BOOST_FORCEINLINE
    auto operator()(V const& v, X const&) const BOOST_NOEXCEPT -> decltype(impl(v))
    {
      return impl( v );
    }
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
