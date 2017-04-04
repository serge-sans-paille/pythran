//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_CONSTANT_CONSTANT_VALUE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_CONSTANT_CONSTANT_VALUE_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4310) // Truncation
#pragma warning(disable: 4309) // Truncation
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_FALLBACK( (typename Constant, typename T)
                                  , boost::dispatch::constant_value_<Constant>
                                  , boost::dispatch::cpu_
                                  , bd::target_<bd::scalar_<bd::unspecified_<T>>>
                                  )
  {
    using value_t = typename detail::constant_traits<Constant,typename T::type>::type;

    BOOST_FORCEINLINE typename value_t::value_type operator()(T const&) const BOOST_NOEXCEPT
    {
      return value_t{};
    }
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
