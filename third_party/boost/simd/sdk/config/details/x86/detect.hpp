//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_X86_DETECT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_X86_DETECT_HPP_INCLUDED

#include <boost/simd/sdk/config/arch/x86.hpp>

#ifdef BOOST_SIMD_ARCH_X86
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/sdk/config/details/detector/get_vendor.hpp>
#include <boost/simd/sdk/config/details/detector/cpuid.hpp>

/*!
 *\file detect.hpp
*/

namespace boost { namespace simd { namespace config { namespace details
{
  inline bool has_bit_set(int value, int bit)
  {
    return (value & (1<<bit)) != 0;
  }

  inline bool x86_detection(int const& bit, int const& function, int const& register_id)
  {
    int regs_x86[4] = {0x00000000,0x00000000,0x00000000,0x00000000};
    config::x86::cpuidex(regs_x86, function, 0);
    return has_bit_set(regs_x86[register_id-1], bit);
  }

  inline bool detect(tag::sse_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(25,0x00000001,4);
    return false;
  }

  inline bool detect(tag::sse2_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(26,0x00000001,4);
    return false;
  }

  inline bool detect(tag::sse3_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(0,0x00000001,3);
    return false;
  }

  inline bool detect(tag::ssse3_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(9,0x00000001,3);
    return false;
  }

  inline bool detect(tag::sse4a_ const&)
  {
    if (x86::get_vendor() == x86::amd)
      return x86_detection(6,0x80000001,3);
    return false;
  }

  inline bool detect(tag::sse4_1_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(19,0x00000001,3);
    return false;
  }

  inline bool detect(tag::sse4_2_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(20,0x00000001,3);
    return false;
  }

  inline bool detect(tag::avx_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(28,0x00000001,3) && x86_detection(27,0x00000001,3);
    return false;
  }

  inline bool detect(tag::fma4_ const&)
  {
    if (x86::get_vendor() == x86::amd)
      return x86_detection(16,0x80000001,3) && x86_detection(27,0x00000001,3);
    return false;
  }

  inline bool detect(tag::xop_ const&)
  {
    if (x86::get_vendor() == x86::amd)
      return x86_detection(11,0x80000001,3) && x86_detection(27,0x00000001,3);
    return false;
  }

  inline bool detect(tag::fma3_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(12,0x00000001,3) && x86_detection(27,0x00000001,3);
    return false;
  }

  inline bool detect(tag::avx2_ const&)
  {
    if (x86::get_vendor() == x86::intel || x86::get_vendor() == x86::amd)
      return x86_detection(5,0x00000007,2) && x86_detection(27,0x00000001,3);
    return false;
  }

} } } }

#endif
#endif
