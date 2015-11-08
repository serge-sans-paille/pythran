//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_HPP_INCLUDED

#if defined(__FAST_MATH__) && !defined(BOOST_SIMD_NO_NANS)
#define BOOST_SIMD_NO_NANS
#endif

#if defined(__FAST_MATH__) && !defined(BOOST_SIMD_NO_MINUSZERO)
#define BOOST_SIMD_NO_MINUSZERO
#endif

#if defined(__FAST_MATH__) && !defined(BOOST_SIMD_NO_INFINITIES)
#define BOOST_SIMD_NO_INFINITIES
#endif

#if defined(__FAST_MATH__) && !defined(BOOST_SIMD_NO_DENORMALS)
#define BOOST_SIMD_NO_DENORMALS
#endif

#if defined(BOOST_SIMD_NO_NANS) && defined(BOOST_SIMD_NO_INFINITIES) && !defined(BOOST_SIMD_NO_INVALIDS)
#define BOOST_SIMD_NO_INVALIDS
#elif defined(BOOST_SIMD_NO_INVALIDS)
#define BOOST_SIMD_NO_NANS
#define BOOST_SIMD_NO_INFINITIES
#endif

#endif
