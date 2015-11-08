//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_DETECTOR_GET_VENDOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_DETECTOR_GET_VENDOR_HPP_INCLUDED

#include <boost/simd/sdk/config/arch/x86.hpp>
#ifdef BOOST_SIMD_ARCH_X86
#include <boost/simd/sdk/config/details/detector/cpuid.hpp>
#include <cstring>

/*!
 *\file get_vendor.hpp
 *\brief Runtime function to get the Vendor Processor.
*/

#define BOOST_SIMD_VENDOR_INTEL "GenuineIntel"
#define BOOST_SIMD_VENDOR_AMD   "AuthenticAMD"

namespace boost { namespace simd { namespace config { namespace x86
{
  enum vendor
  {
    intel,
    amd
  };

  inline static bool str_match(const int abcd[4], const char* vendor)
  {
    return ( !std::memcmp(abcd + 1, vendor,     4)
          && !std::memcmp(abcd + 2, vendor + 8, 4)
          && !std::memcmp(abcd + 3, vendor + 4, 4) );
  }

  inline int get_vendor()
  {
    static const int function = 0x00000000;
    int regs_x86[4];
    config::x86::cpuid(regs_x86, function);
    if( str_match(regs_x86, BOOST_SIMD_VENDOR_INTEL) ) return intel;
    else if( str_match(regs_x86, BOOST_SIMD_VENDOR_AMD) ) return amd;
    else return -1;
  }
} } } }

#endif

#endif
