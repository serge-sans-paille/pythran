//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // Whenever we store with an offset
  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Src, typename Pointer, typename X, typename A2)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          , bd::scalar_<bd::integer_<A2>>
                          )
  {
    BOOST_FORCEINLINE void operator()(Src const& a0, Pointer a1, A2 const & a2) const BOOST_NOEXCEPT
    {
      bs::aligned_store(a0,a1+a2);
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_store is generally check + calling store
  BOOST_DISPATCH_OVERLOAD( aligned_store_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<A0>,X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<A1>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator()(const A0& a0, A1  a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(a1,A0::alignment)
                      , "boost::simd::aligned_store was performed on an unaligned pointer of integer"
                      );
      bs::store(a0, a1);
    }
  };
} } }

#endif
