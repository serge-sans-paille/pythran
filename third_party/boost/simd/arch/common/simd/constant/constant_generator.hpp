//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_CONSTANT_CONSTANT_GENERATOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_CONSTANT_CONSTANT_GENERATOR_HPP_INCLUDED

#if defined(BOOST_SIMD_DETECTED)
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/config.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_FALLBACK( (typename T, typename V, typename X)
                                  , boost::dispatch::constant_value_<tag::constant_>
                                  , bd::cpu_
                                  , bd::scalar_<bd::unspecified_<V>>
                                  , bd::target_< bs::pack_<bd::unspecified_<T>,X> >
                                  )
  {
    using value_t   = typename T::type::value_type;
    using scalar_t  = decltype(bd::functor<tag::constant_>{}(V(),bd::as_<value_t>()));
    using result_t  = typename T::type::template rebind<scalar_t>;

    BOOST_FORCEINLINE result_t operator()(V const& v, T const&) const
    {
      return result_t{ bd::functor<tag::constant_>{}(v,bd::as_<value_t>()) };
    }
  };
} } }

#endif

#endif
