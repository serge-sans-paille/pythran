//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( aligned_load_
                            , (typename Target, typename Pointer)
                            , (bs::is_pointing_to<Pointer,typename Target::type::value_type>)
                            , bs::vmx_
                            , bd::pointer_<bd::scalar_<bd::arithmetic_<Pointer>>,1u>
                            , bd::target_<bs::pack_<bd::arithmetic_<Target>,bs::vmx_>>
                            )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer p, Target const&) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p,target::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer of double"
                      );

      return vec_ld(0, p);
    }
  };
} } }

#endif
