//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_SSE4_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_SSE4_2_HPP_INCLUDED

#if defined(__SSE4_2__)
#  ifndef BOOST_SIMD_HAS_SSE4_2_SUPPORT
#    define BOOST_SIMD_HAS_SSE4_2_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_SSE4_2_SUPPORT) && !defined(_MSC_VER)
#  undef BOOST_SIMD_HAS_SSE4_2_SUPPORT
#endif

#if defined(BOOST_SIMD_HAS_SSE4_2_SUPPORT) && !defined(BOOST_SIMD_HAS_SSE4_1_SUPPORT)
#  define BOOST_SIMD_HAS_SSE4_1_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_SSE4_2_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// SSE4_2 extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_SSE4_2
#define BOOST_SIMD_SSE_FAMILY
#define BOOST_SIMD_STRING             "SSE4_2"
#define BOOST_SIMD_STRING_LIST        "SSE2 SSE3 SSSE3 SSE4_1 SSE4_2"
#define BOOST_SIMD_BYTES              16
#define BOOST_SIMD_BITS               128
#define BOOST_SIMD_CARDINALS          (2)(4)(8)(16)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::sse_)

#ifndef BOOST_SIMD_DEFAULT_EXTENSION
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::sse_
#endif

#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::sse4_2_
#define BOOST_SIMD_SIMD_HAS_ALL_TYPES

#include <nmmintrin.h>

#include <boost/simd/sdk/simd/extensions/meta/sse.hpp>

#endif
#endif
