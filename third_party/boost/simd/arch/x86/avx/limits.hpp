//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_LIMITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_LIMITS_HPP_INCLUDED

#include <boost/simd/arch/x86/tags.hpp>
#include <boost/simd/arch/common/limits.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  template<> struct limits<boost::simd::avx_>
  {
    struct largest_integer
    {
      template<typename Sign> struct apply : boost::dispatch::make_integer<8,Sign> {};
    };

    struct smallest_integer
    {
      template<typename Sign> struct apply : boost::dispatch::make_integer<1,Sign> {};
    };

    using parent = boost::simd::sse2_;

    using smallest_real = float;
    using largest_real  = double;

    enum { bits = 256, bytes = 32 };

    using supported_types = nsm::list < float,double
                                      , std::int8_t , std::int16_t , std::int32_t , std::int64_t
                                      , std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
                                      >;
  };
} }

#endif

