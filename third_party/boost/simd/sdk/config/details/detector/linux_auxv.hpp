//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_DETECTOR_LINUX_AUXV_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_DETECTOR_LINUX_AUXV_HPP_INCLUDED

#ifdef BOOST_SIMD_OS_LINUX
#include <linux/auxvec.h>
#include <fcntl.h>
#include <unistd.h>
#include <boost/cstdint.hpp>

namespace boost { namespace simd { namespace config { namespace linux_
{
  inline uintptr_t auxv(uintptr_t type)
  {
    int fd;
    uintptr_t auxv[2];

    fd = open("/proc/self/auxv", O_RDONLY);
    if (fd >= 0)
    {
      while(read(fd, &auxv, sizeof(auxv)) == sizeof(auxv))
      {
        if (auxv[0] == type)
        {
          close(fd);
          return auxv[1];
        }
      }
      close(fd);
    }
    return 0;
  }

  inline unsigned int hwcap()
  {
      return auxv(AT_HWCAP);
  }

} } } }

#endif

#endif
