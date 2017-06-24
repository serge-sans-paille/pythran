//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/shuffle/default_matcher.hpp>
#include <boost/simd/function/extract.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd  = boost::dispatch;
  namespace bs  = boost::simd;
  namespace bsd = boost::simd::detail;

  // -----------------------------------------------------------------------------------------------
  // Unary common cases
  BOOST_DISPATCH_OVERLOAD_IF( shuffle_
                            , (int... Ps, typename A0, typename X)
                            , (nsm::bool_<A0::static_size==sizeof...(Ps)>)
                            , bd::cpu_
                            , bsd::pattern_<Ps...>
                            , bs::pack_< bd::unspecified_<A0>, X >
                            )
  {
    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, A0 const& a0) const
    {
      return detail::shuffler<detail::default_matcher, bsd::pattern_<Ps...>>::process(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Binary common cases
  BOOST_DISPATCH_OVERLOAD_IF( shuffle_
                            , (int... Ps, typename A0, typename X)
                            , (nsm::bool_<A0::static_size==sizeof...(Ps)>)
                            , bd::cpu_
                            , bsd::pattern_<Ps...>
                            , bs::pack_< bd::unspecified_<A0>, X >
                            , bs::pack_< bd::unspecified_<A0>, X >
                            )
  {
    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, A0 const& a0, A0 const& a1) const
    {
      return detail::shuffler<detail::default_matcher, bsd::pattern_<Ps...>>::process(a0,a1);
    }
  };
} } }

#endif
