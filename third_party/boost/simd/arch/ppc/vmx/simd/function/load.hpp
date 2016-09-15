//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_LOAD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_LOAD_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( load_
                            , (typename Target, typename Pointer)
                            , (bs::is_pointing_to<Pointer,typename Target::type::value_type>)
                            , bs::vmx_
                            , bd::pointer_<bd::scalar_<bd::arithmetic_<Pointer>>,1u>
                            , bd::target_<bs::pack_<bd::arithmetic_<Target>,bs::vmx_>>
                            )
  {
    BOOST_FORCEINLINE typename Target::type operator()(Pointer a0, Target const&) const
    {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wdeprecated"
      return vec_perm(vec_ld(0, a0), vec_ld(16, a0), vec_lvsl(0, a0));
      #pragma GCC diagnostic pop
    }
  };
} } }

#endif
