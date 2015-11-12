//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_POWERPC_DETECT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_POWERPC_DETECT_HPP_INCLUDED

#include <boost/simd/sdk/config/arch/powerpc.hpp>

#ifdef BOOST_SIMD_ARCH_POWERPC
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/sdk/config/os.hpp>

#if defined(BOOST_SIMD_OS_LINUX)
#include <boost/simd/sdk/config/details/detector/linux_auxv.hpp>
#include <asm/cputable.h>
#elif defined(BOOST_SIMD_OS_MACOS)
#include <Gestalt.h>
#endif

namespace boost { namespace simd { namespace config { namespace details
{
  inline bool detect(tag::vmx_ const&)
  {
#if defined(BOOST_SIMD_OS_LINUX)
    return config::linux_::hwcap() & PPC_FEATURE_HAS_ALTIVEC;
#elif defined(BOOST_SIMD_OS_MACOS)
    long cpuAttributes;
    bool hasAltiVec = false;
    OSErr err = Gestalt( gestaltPowerPCProcessorFeatures, &cpuAttributes );
    if( noErr == err ) { hasAltiVec = ( 1 << gestaltPowerPCHasVectorInstructions) & cpuAttributes; }
    return hasAltiVec;
#else
    return false;
#endif
  }

} } } }

#endif

#endif
