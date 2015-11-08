//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_SSE4A_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_SSE4A_HPP_INCLUDED

#if defined(__SSE4A__)
#  ifndef BOOST_SIMD_HAS_SSE4A_SUPPORT
#    define BOOST_SIMD_HAS_SSE4A_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_SSE4A_SUPPORT) && !defined(_MSC_VER)
#  undef BOOST_SIMD_HAS_SSE4A_SUPPORT
#endif

#if defined(BOOST_SIMD_HAS_SSE4A_SUPPORT) && !defined(BOOST_SIMD_HAS_SSE3_SUPPORT)
#  define BOOST_SIMD_HAS_SSE3_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_SSE4A_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// SSE4A extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_SSE4A
#define BOOST_SIMD_SSE_FAMILY
#define BOOST_SIMD_STRING             "SSE4A"
#define BOOST_SIMD_STRING_LIST        "SSE2 SSE3 SSE4A"
#define BOOST_SIMD_BYTES              16
#define BOOST_SIMD_BITS               128
#define BOOST_SIMD_CARDINALS          (2)(4)(8)(16)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::sse_)

#ifndef BOOST_SIMD_DEFAULT_EXTENSION
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::sse_
#endif

#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::sse4a_
#define BOOST_SIMD_SIMD_HAS_ALL_TYPES

#include <ammintrin.h>

#include <boost/simd/sdk/simd/extensions/meta/sse.hpp>

#endif
#endif
