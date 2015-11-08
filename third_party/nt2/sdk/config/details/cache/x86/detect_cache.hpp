//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONFIG_DETAILS_CACHE_X86_DETECT_CACHE_HPP_INCLUDED
#define NT2_SDK_CONFIG_DETAILS_CACHE_X86_DETECT_CACHE_HPP_INCLUDED

#include <boost/simd/sdk/config/arch.hpp>

#ifdef BOOST_SIMD_ARCH_X86
#include <boost/simd/sdk/config/details/detector/cpuid.hpp>
#include <boost/simd/sdk/config/details/detector/get_vendor.hpp>
#include <boost/assert.hpp>

#define NT2_CACHE_DETECT_DEFINED

namespace nt2{ namespace config{ namespace details{

  inline int get_range(int reg, int begin, int end)
  {
    int mask=0x00000000;
    BOOST_ASSERT_MSG( begin < end, "Invalid iterators");
    for(int i = 0; i < (end - begin); i++) { mask <<= 1; mask |= 0x1; }
    return ((reg >> begin) & mask);
  }

  template<class Seq>
  inline void detect_cache(Seq& cache_sizes_, Seq& cache_line_sizes_)
  {
    int regs[4] = {0,0,0,0};
    int cache_ecx = 0;
    int type;

    switch(boost::simd::config::x86::get_vendor())
    {
    case boost::simd::config::x86::intel :

      do{
        boost::simd::config::x86::cpuidex(regs, 0x00000004, cache_ecx);

        int level      = (regs[0] & 0x000000E0) >> 5;
        int ways       = (regs[1] & 0xFFC00000) >> 22;
        int partitions = (regs[1] & 0x003FF000) >> 12;
        int line_size  = (regs[1] & 0x00000FFF) >>  0;
        int sets       = (regs[2]);
        int size       = (ways+1)*(partitions+1)*(line_size+1)*(sets+1);
        type           = (regs[0] & 0x0000001F);

        switch(type)
        {
        case 1 :  *(&cache_sizes_[0]+level) = size/1024;
                  cache_line_sizes_[level]  = line_size+1;
                  break;
        case 2 :  cache_sizes_[0]      = size/1024;
                  cache_line_sizes_[0] = line_size+1;
                  break;
        case 3 :  *(&cache_sizes_[0]+level) = size/1024;
                  cache_line_sizes_[level]  = line_size+1;
                  break;
        default : break;
        }

        cache_ecx++;
      }while(type != 0x00000000);

      break;

    case boost::simd::config::x86::amd :

      boost::simd::config::x86::cpuidex(regs,0x80000005,0);
      cache_line_sizes_[0] = regs[2] & 0x000000FF;
      cache_sizes_[0]      = regs[2] >> 24;
      cache_line_sizes_[1] = regs[3] & 0x000000FF;
      cache_sizes_[1]      = regs[3] >> 24;

      regs[0] = regs[1] = regs[2] = regs[3] = 0;
      boost::simd::config::x86::cpuidex(regs,0x80000006,0);

      if(get_range(regs[0], 28, 32) != 0)
      {
        cache_line_sizes_[2] = regs[2] & 0x000000FF;
        cache_sizes_[2] = regs[2] >> 16;
        cache_line_sizes_[3] = regs[3] & 0x000000FF;
        cache_sizes_[3] = (((regs[3] & 0xFFFC000) >> 18)*512); // D[31;18] = l3 cache size in 512KB
      }

      break;

    default : break;
    }
  }
} } }

#endif

#endif
