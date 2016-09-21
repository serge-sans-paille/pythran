//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( aligned_store_
                            , (typename Src, typename Pointer)
                            , (bs::is_pointing_to<Pointer,typename Src::value_type>)
                            , bs::vmx_
                            , bs::pack_<bd::arithmetic_<Src>,bs::vmx_>
                            , bd::pointer_<bd::scalar_<bd::arithmetic_<Pointer>>,1u>
                            )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer p) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p, Src::alignment)
                      , "boost::simd::aligned_store was performed on an unaligned pointer"
                      );

      vec_st(s.storage(), 0, p);
    }
  };
} } }

#endif
