//==============================================================================
//         Copyright 2014 MetaScale SAS
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_MIC_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_MIC_HPP_INCLUDED

#if defined(__MIC__)
#  ifndef BOOST_SIMD_HAS_MIC_SUPPORT
#    define BOOST_SIMD_HAS_MIC_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_MIC_SUPPORT) && !defined(_MSC_VER)
#  undef BOOST_SIMD_HAS_MIC_SUPPORT
#endif

#if defined(BOOST_SIMD_HAS_MIC_SUPPORT) && !defined(BOOST_SIMD_HAS_SSE2_SUPPORT)
#  define BOOST_SIMD_HAS_SSE2_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_MIC_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// MIC extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_MIC
#define BOOST_SIMD_STRING             "MIC"
#define BOOST_SIMD_STRING_LIST        "MIC SSE2"
#define BOOST_SIMD_BYTES              64
#define BOOST_SIMD_BITS               512
#define BOOST_SIMD_CARDINALS          (8)(16)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::mic_)(::boost::simd::tag::sse_)

#ifndef BOOST_SIMD_DEFAULT_EXTENSION
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::mic_
#endif

#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::mic_

#define BOOST_SIMD_SIMD_REAL_TYPES (double)(float)

#define BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES (boost::simd::uint64_t)(boost::simd::uint32_t)
#define BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES (boost::simd::int64_t)(boost::simd::int32_t)

#define BOOST_SIMD_SIMD_INT_CONVERT_TYPES  (boost::simd::int64_t)(boost::simd::int32_t)
#define BOOST_SIMD_SIMD_UINT_CONVERT_TYPES (boost::simd::uint64_t)(boost::simd::uint32_t)

#define BOOST_SIMD_SIMD_REAL_GROUPABLE_TYPES (double)
#define BOOST_SIMD_SIMD_REAL_SPLITABLE_TYPES (float)

#define BOOST_SIMD_SIMD_GROUPABLE_TYPES (double)(boost::simd::int64_t)(boost::simd::uint64_t)
#define BOOST_SIMD_SIMD_SPLITABLE_TYPES (float)(boost::simd::int32_t)(boost::simd::uint32_t)

#include <immintrin.h>
#include <boost/simd/sdk/simd/extensions/meta/mic.hpp>

#endif
#endif
