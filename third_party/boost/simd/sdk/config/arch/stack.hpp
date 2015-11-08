//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_ARCH_STACK_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_ARCH_STACK_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/version.hpp>

// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=16660
#if defined( __arm__ ) || defined( _ARM )
  #if defined( __APPLE__ )
  // http://developer.apple.com/library/ios/#documentation/Xcode/Conceptual/iPhoneOSABIReference/Articles/ARMv6FunctionCallingConventions.html
    #define BOOST_SIMD_ARCH_ALIGNMENT 4
  #else
  // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ihi0042d/index.html
    #define BOOST_SIMD_ARCH_ALIGNMENT 8
  #endif
#elif (defined(__clang__) || defined( __GNUC__ ) ) && defined( __i386__ )
  #define BOOST_SIMD_ARCH_ALIGNMENT 16
#elif defined( _WIN32 )
  // http://msdn.microsoft.com/en-us/library/aa290049(v=vs.71).aspx
  #if defined( _WIN64 )
    #define BOOST_SIMD_ARCH_ALIGNMENT 16
  #else
    #define BOOST_SIMD_ARCH_ALIGNMENT 4
  #endif
#else
#define BOOST_SIMD_ARCH_ALIGNMENT 16
#endif

// Fix for GCC Bug 35271 : http://gcc.gnu.org/bugzilla/show_bug.cgi?id=35271
#if defined( __GNUC__ ) && (BOOST_SIMD_GCC_VERSION < 40203)
#define BOOST_SIMD_ALLOCA_ALIGNMENT 8
#else
#define BOOST_SIMD_ALLOCA_ALIGNMENT BOOST_SIMD_ARCH_ALIGNMENT
#endif

#endif
