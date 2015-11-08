//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_POWERPC_VSX_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_POWERPC_VSX_HPP_INCLUDED

#if defined(__VSX__)
#  ifndef BOOST_SIMD_HAS_VSX_SUPPORT
#    define BOOST_SIMD_HAS_VSX_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_VSX_SUPPORT)
#  undef BOOST_SIMD_HAS_VSX_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_VSX_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// Include the proper intrinsic include. Depending of the option used by the
// compiler (-faltivec or -maltivec), we need to include altivec.h or not.
////////////////////////////////////////////////////////////////////////////////
#if !defined(__APPLE_CC__) || __APPLE_CC__ <= 1 || __GNUC__ >= 4
#include <altivec.h>
#endif

#ifdef bool
#undef bool
#endif
#ifdef pixel
#undef pixel
#endif
#ifdef vector
#undef vector
#endif

#if defined(__IBMCPP__) || defined(__MWERKS__)
#define __bool bool
#endif

////////////////////////////////////////////////////////////////////////////////
// Altivec PPC extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_ALTIVEC
#define BOOST_SIMD_STRING             "VSX"
#define BOOST_SIMD_STRING_LIST        "VMX VSX"
#define BOOST_SIMD_VMX_FAMILY
#define BOOST_SIMD_BYTES              16
#define BOOST_SIMD_BITS               128
#define BOOST_SIMD_CARDINALS          (2)(4)(8)(16)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::vmx_)

#ifndef BOOST_SIMD_DEFAULT_EXTENSION
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::vmx_
#endif

#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::vsx_
#define BOOST_SIMD_NO_DENORMALS
#define BOOST_SIMD_SIMD_HAS_ALL_TYPES

#include <boost/simd/sdk/simd/extensions/meta/vmx.hpp>

#endif
#endif
