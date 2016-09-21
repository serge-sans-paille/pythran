//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_AUTOMAP_SLICE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_AUTOMAP_SLICE_HPP_INCLUDED

#if BOOST_HW_SIMD_X86_OR_AMD >= BOOST_HW_SIMD_X86_AVX_VERSION
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/decorator.hpp>
#include <boost/simd/arch/common/tags.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/detail/diagnostic.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  //------------------------------------------------------------------------------------------------
  // auto-map for regular calls over sliceable registers
  BOOST_DISPATCH_OVERLOAD_FALLBACK( (typename F, typename... Args)
                                  , bd::elementwise_<F>
                                  , bs::avx_
                                  , bs::pack_<bd::fundamental_<Args>, bs::avx_>...
                                  )
  {
    using func_t = bd::functor<F>;

    BOOST_FORCEINLINE
    auto  operator()( const Args&... a) const BOOST_NOEXCEPT
          -> decltype( combine( func_t{}( slice_low (a) ... ), func_t{}( slice_high(a) ... ) ) )
    {
      BOOST_SIMD_DIAG("Sliceable automap for: " << *this);
      return combine( func_t{}( slice_low (a) ... ), func_t{}( slice_high(a) ... ) );
    }
  };

  //------------------------------------------------------------------------------------------------
  // auto-map for calls with options over sliceable registers
  BOOST_DISPATCH_OVERLOAD_FALLBACK( (typename F, typename Opt, typename... Args)
                                  , bd::elementwise_<F>
                                  , bs::avx_
                                  , bd::function_<Opt>
                                  , bs::pack_<bd::fundamental_<Args>, bs::avx_>...
                                  )
  {
    using func_t = bd::functor<F>;

    BOOST_FORCEINLINE
    auto  operator()(bd::functor<Opt> const& o, const Args&... a) const BOOST_NOEXCEPT
          -> decltype( combine( func_t{}(o, slice_low (a)...), func_t{}(o,slice_high(a)...) ) )
    {
      BOOST_SIMD_DIAG("Sliceable automap with options for: " << *this);
      return combine( func_t{}(o, slice_low (a)...), func_t{}(o, slice_high(a)...) );
    }
  };

  //------------------------------------------------------------------------------------------------
  // auto-map for decorated calls over sliceable registers
  BOOST_DISPATCH_OVERLOAD_FALLBACK( (typename F, typename Decorator, typename... Args)
                                  , bd::elementwise_<F>
                                  , bs::avx_
                                  , bs::decorator_<Decorator>
                                  , bs::pack_<bd::fundamental_<Args>, bs::avx_>...
                                  )
  {
    using func_t = decltype(detail::decorator<Decorator>()(bd::functor<F>()));

    BOOST_FORCEINLINE
    auto  operator()(Decorator const& d, const Args&... a) const BOOST_NOEXCEPT
          -> decltype( combine( func_t{}(slice_low (a)...), func_t{}(slice_high(a)...) ) )
    {
      BOOST_SIMD_DIAG("Sliceable automap with decorator" << d << " for: " << *this);
      boost::ignore_unused(d);
      return combine( func_t{}( slice_low (a) ... ), func_t{}( slice_high(a) ... ) );
    }
  };

  //------------------------------------------------------------------------------------------------
  // auto-map for decorated calls with options over sliceable registers
  BOOST_DISPATCH_OVERLOAD_FALLBACK( (typename F, typename Decorator, typename Opt, typename... Args)
                                  , bd::elementwise_<F>
                                  , bs::avx_
                                  , bs::decorator_<Decorator>
                                  , bd::function_<Opt>
                                  , bs::pack_<bd::fundamental_<Args>, bs::avx_>...
                                  )
  {
    using func_t = decltype(detail::decorator<Decorator>()(bd::functor<F>()));

    BOOST_FORCEINLINE auto
    operator()(Decorator const& d, bd::functor<Opt> const& o, const Args&... a) const BOOST_NOEXCEPT
          -> decltype( combine( func_t{}(o,slice_low (a)...), func_t{}(o,slice_high(a)...) ) )
    {
      BOOST_SIMD_DIAG ( "Sliceable automap with decorator"  << d
                                                            << " for: " << *this << " options: "
                                                            << o
                      );
      boost::ignore_unused(d);
      return combine( func_t{}(o, (a) ... ), func_t{}(o,slice_high(a) ... ) );
    }
  };
} } }
#endif

#endif
