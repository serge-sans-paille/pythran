//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FREXP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_FREXP_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/ifrexp.hpp>
#include <boost/simd/function/tofloat.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE std::pair<A0,A0> operator()(A0 const& a0) const
    {
      auto r = ifrexp(a0);
      return {r.first, tofloat(r.second)};
    }
  };

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE std::pair<A0,A0> operator()(bs::pedantic_tag const&, A0 const& a0) const
    {
      auto r = pedantic_(ifrexp)(a0);
      return {r.first, tofloat(r.second)};
    }
  };

  BOOST_DISPATCH_OVERLOAD ( frexp_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::raw_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE std::pair<A0,A0> operator()(bs::raw_tag const&, A0 const& a0) const
    {
      auto r = raw_(ifrexp)(a0);
      return {r.first, tofloat(r.second)};
    }
  };
} } }

#endif
