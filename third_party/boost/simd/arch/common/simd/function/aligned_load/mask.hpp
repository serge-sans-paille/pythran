//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_LOAD_MASK_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_LOAD_MASK_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/mask.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // aligned_load data from a masked pointer of whatever in a pack
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Pointer, typename Zero, typename Target, typename TX)
                          , bd::cpu_
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>, Zero>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,TX>>
                          )
  {
    using target_t  = typename Target::type;

    BOOST_FORCEINLINE
    target_t operator()(Pointer const& p, Target const&) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p.get(),target_t::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer"
                      );

      return load<target_t>(p);
    }
  };
} } }

#endif
