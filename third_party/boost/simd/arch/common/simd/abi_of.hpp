//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_ABI_OF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_ABI_OF_HPP_INCLUDED

#include <boost/simd/arch/common/tags.hpp>
#include <cstdint>

namespace boost { namespace simd { namespace ext
{
  template<typename Type, std::size_t Cardinal, typename Enable = void> struct abi_of
  {
    using type = boost::simd::simd_emulation_;
  };
} } }

#endif
