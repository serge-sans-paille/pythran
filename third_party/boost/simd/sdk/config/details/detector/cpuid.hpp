//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_DETECTOR_CPUID_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_DETECTOR_CPUID_HPP_INCLUDED

/*!
 *\file cpuid.hpp
 *\brief cpuid function to get x86 processor infos
*/

#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/config/os.hpp>

#if defined(BOOST_SIMD_COMPILER_MSVC)
#include <intrin.h>
#endif

namespace boost { namespace simd { namespace config { namespace x86
{

  inline void cpuid(int CPUInfo[4],int InfoType)
  {
#if defined(BOOST_SIMD_ARCH_X86)

#if defined(BOOST_SIMD_COMPILER_GCC_LIKE)
    enum e_x_enum { eax,ebx,ecx,edx };

#if !defined(__PIC__) || defined(BOOST_SIMD_ARCH_X86_64)
    __asm__ __volatile__
    (
      "cpuid"
    : "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
    , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
    : "a" (InfoType)
    : "cc"
    );
#else
    __asm__ __volatile__
    (
      "pushl %%ebx      \n\t" /* save %ebx */
      "cpuid            \n\t"
      "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
      "popl %%ebx       \n\t" /* restore the old %ebx */
    : "=a"(CPUInfo[eax]), "=r"(CPUInfo[ebx])
    , "=c"(CPUInfo[ecx]), "=d"(CPUInfo[edx])
    : "a"(InfoType)
    : "cc"
    );
#endif

#elif defined(BOOST_SIMD_COMPILER_MSVC)
    __cpuid(CPUInfo,InfoType);
#else
#error compiler not supported
#endif

#endif
  }

  inline void cpuidex(int CPUInfo[4],int InfoType, int ECXValue)
  {
#if defined(BOOST_SIMD_ARCH_X86)

#if defined(BOOST_SIMD_COMPILER_GCC_LIKE)
    enum { eax,ebx,ecx,edx };

#if !defined(__PIC__) || defined(BOOST_SIMD_ARCH_X86_64)
    __asm__ __volatile__
    (
      "cpuid"
    : "=a" (CPUInfo[eax]), "=b" (CPUInfo[ebx])
    , "=c" (CPUInfo[ecx]), "=d" (CPUInfo[edx])
    : "a" (InfoType), "c" (ECXValue)
    : "cc"
    );
#else
    __asm__ __volatile__
    (
      "pushl %%ebx      \n\t" /* save %ebx */
      "cpuid            \n\t"
      "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
      "popl %%ebx       \n\t" /* restore the old %ebx */
    : "=a"(CPUInfo[eax]), "=r"(CPUInfo[ebx])
    , "=c"(CPUInfo[ecx]), "=d"(CPUInfo[edx])
    : "a"(InfoType), "c" (ECXValue)
    : "cc"
    );
#endif

#elif defined(BOOST_SIMD_COMPILER_MSVC)
#if _MSC_VER > 1500
    __cpuidex(CPUInfo,InfoType,ECXValue);
#else
    __asm
    {
      mov    esi,CPUInfo
      mov    eax,InfoType
      mov    ecx,ECXValue
      cpuid
      mov    dword ptr [esi], eax
      mov    dword ptr [esi+4],ebx
      mov    dword ptr [esi+8],ecx
      mov    dword ptr [esi+0Ch],edx
    }
#endif
#else
#error compiler not supported
#endif

#endif
  }

} } } }


#endif
