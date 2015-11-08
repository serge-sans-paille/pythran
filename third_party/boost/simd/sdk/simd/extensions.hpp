//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Regular SIMD extensions
////////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SIMD_DISABLE_SIMD) && !defined(NVCC)
#include <boost/simd/sdk/simd/extensions/extensions.hpp>
#endif

#include <boost/simd/sdk/simd/extensions/common/common.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>

#include <boost/dispatch/functor/forward.hpp>

BOOST_DISPATCH_COMBINE_SITE( BOOST_SIMD_DEFAULT_SITE )

#endif
