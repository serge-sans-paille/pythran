//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_POWERPC_QPX_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_POWERPC_QPX_HPP_INCLUDED

#if defined(__VECTOR4DOUBLE__)
#  ifndef BOOST_SIMD_HAS_QPX_SUPPORT
#    define BOOST_SIMD_HAS_QPX_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_QPX_SUPPORT)
#  undef BOOST_SIMD_HAS_QPX_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_QPX_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// Altivec PPC extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_ALTIVEC
#define BOOST_SIMD_STRING             "QPX"
#define BOOST_SIMD_STRING_LIST        "QPX"
#define BOOST_SIMD_VMX_FAMILY
#define BOOST_SIMD_BYTES              32
#define BOOST_SIMD_BITS               256
#define BOOST_SIMD_CARDINALS          (8)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::qpx_)

#ifndef BOOST_SIMD_DEFAULT_EXTENSION
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::qpx_
#endif

#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::qpx_
#define BOOST_SIMD_NO_DENORMALS

#define BOOST_SIMD_SIMD_REAL_TYPES (double)

#define BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES
#define BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES

#define BOOST_SIMD_SIMD_INT_CONVERT_TYPES
#define BOOST_SIMD_SIMD_UINT_CONVERT_TYPES

#define BOOST_SIMD_SIMD_GROUPABLE_TYPES
#define BOOST_SIMD_SIMD_SPLITABLE_TYPES

#define BOOST_SIMD_SIMD_REAL_GROUPABLE_TYPES
#define BOOST_SIMD_SIMD_REAL_SPLITABLE_TYPES

#include <boost/simd/sdk/simd/extensions/meta/qpx.hpp>

#endif
#endif
