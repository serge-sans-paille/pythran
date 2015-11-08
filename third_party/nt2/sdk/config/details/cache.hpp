//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONFIG_DETAILS_CACHE_HPP_INCLUDED
#define NT2_SDK_CONFIG_DETAILS_CACHE_HPP_INCLUDED

#include <nt2/sdk/config/details/cache/detect_cache.hpp>
#include <boost/simd/sdk/config/os.hpp>
#include <boost/array.hpp>

#define NT2_MAX_CACHE_LEVEL 4

#ifndef NT2_CACHE_DETECT_DEFINED

#if defined(BOOST_SIMD_OS_LINUX) && !defined(__ANDROID__)
#include <unistd.h>

namespace nt2 { namespace config { namespace details
{
  template<class Seq>
  inline void detect_cache(Seq& cache_sizes_, Seq& cache_line_sizes_)
  {
    cache_line_sizes_[0] = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    cache_sizes_[0] = sysconf(_SC_LEVEL1_DCACHE_SIZE);

    cache_line_sizes_[1] = sysconf(_SC_LEVEL2_CACHE_LINESIZE);
    cache_sizes_[1] = sysconf(_SC_LEVEL2_CACHE_SIZE);

    cache_line_sizes_[2] = sysconf(_SC_LEVEL3_CACHE_LINESIZE);
    cache_sizes_[2] = sysconf(_SC_LEVEL3_CACHE_SIZE);

    cache_line_sizes_[3] = sysconf(_SC_LEVEL4_CACHE_LINESIZE);
    cache_sizes_[3] = sysconf(_SC_LEVEL4_CACHE_SIZE);
  }
} } }

#elif defined(BOOST_SIMD_OS_MAC_OS)
#include <sys/sysctl.h>

namespace nt2 { namespace config { namespace details
{
  template<class Seq>
  inline void detect_cache(Seq& cache_sizes_, Seq& cache_line_sizes_)
  {
    size_t line_size = 0;
    size_t sizeof_size_t = sizeof(size_t);
    sysctlbyname("hw.cachelinesize", &line_size, &sizeof_size_t, 0, 0);
    for(size_t i=0; i!=3u; ++i)
      cache_line_sizes_[i] = line_size;

    size_t l1_cache = 0;
    sysctlbyname("hw.l1dcachesize", &l1_cache, &sizeof_size_t, 0, 0);
    cache_sizes_[0] = l1_cache;

    size_t l2_cache = 0;
    sysctlbyname("hw.l2cachesize", &l2_cache, &sizeof_size_t, 0, 0);
    cache_sizes_[1] = l2_cache;

    size_t l3_cache = 0;
    sysctlbyname("hw.l3cachesize", &l3_cache, &sizeof_size_t, 0, 0);
    cache_sizes_[2] = l3_cache;
  }
} } }

#elif defined(BOOST_SIMD_OS_WINDOWS)
#ifndef NOMINMAX
  #define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

typedef BOOL (WINAPI *LPFN_GLPI)(SYSTEM_LOGICAL_PROCESSOR_INFORMATION*, DWORD*);

namespace nt2 { namespace config { namespace details
{
  template<class Seq>
  inline void detect_cache(Seq& cache_sizes_, Seq& cache_line_sizes_)
  {
    size_t line_size = 0;
    DWORD buffer_size = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

    LPFN_GLPI pGetLogicalProcessorInformation = (LPFN_GLPI) GetProcAddress(GetModuleHandle(TEXT("kernel32")),"GetLogicalProcessorInformation");
    if(!pGetLogicalProcessorInformation)
      return;

    if(!pGetLogicalProcessorInformation(0, &buffer_size))
      return;

    buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
    if(!pGetLogicalProcessorInformation(&buffer[0], &buffer_size))
    {
      free(buffer);
      return;
    }

    for(DWORD i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i)
    {
      if (buffer[i].Relationship == RelationCache)
      {
        size_t idx = buffer[i].Cache.Level-1;
        if(idx >= NT2_MAX_CACHE_LEVEL)
          continue;

        cache_sizes_[idx] = buffer[i].Cache.Size;
        cache_line_sizes_[idx] = buffer[i].Cache.LineSize;
      }
    }

    free(buffer);
    return line_size;
  }
} } }

#else

// unknown system
namespace nt2 { namespace config { namespace details
{
  template<class Seq>
  inline void detect_cache(Seq&, Seq&)
  {
    // dummy detect_cache
    // by default all is zero
  }
} } }

#endif

#endif /* NT2_CACHE_DETECT_DEFINED */

namespace nt2 { namespace config { namespace details
{
  inline
  boost::array< boost::array<int, NT2_MAX_CACHE_LEVEL>
              , 2
              >& init_cache()
  {
    typedef boost::array<int, NT2_MAX_CACHE_LEVEL> vector_type;
    static  boost::array<vector_type, 2> cache_infos;
    static  bool is_init = false;
    if(!is_init)
    {
      for(int i = 0; i < NT2_MAX_CACHE_LEVEL; i++)
        cache_infos[0][i] = cache_infos[1][i] = 0;
      details::detect_cache<vector_type>(cache_infos[0], cache_infos[1]);
      is_init = true;
      return cache_infos;
    }
    else return cache_infos;
  }
} } }


#endif
