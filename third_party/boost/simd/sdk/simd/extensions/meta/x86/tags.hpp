//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_X86_TAGS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_X86_TAGS_HPP_INCLUDED

#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/simd/sdk/simd/extensions/meta/common/tags.hpp>
#include <boost/simd/sdk/config/arch.hpp>

namespace boost { namespace simd { namespace tag
{
  // Tag hierarchy for SSE extensions
  BOOST_DISPATCH_HIERARCHY_CLASS(sse_, simd_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse2_, sse_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse3_, sse2_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse4a_, sse3_);
#ifdef BOOST_SIMD_ARCH_AMD
  BOOST_DISPATCH_HIERARCHY_CLASS(ssse3_, sse4a_);
#else
  BOOST_DISPATCH_HIERARCHY_CLASS(ssse3_, sse3_);
#endif
  BOOST_DISPATCH_HIERARCHY_CLASS(sse4_1_, ssse3_);
  BOOST_DISPATCH_HIERARCHY_CLASS(sse4_2_, sse4_1_);
  BOOST_DISPATCH_HIERARCHY_CLASS(avx_, sse4_2_);
  BOOST_DISPATCH_HIERARCHY_CLASS(fma4_, avx_);
  BOOST_DISPATCH_HIERARCHY_CLASS(xop_, fma4_);
#ifdef BOOST_SIMD_ARCH_AMD
  BOOST_DISPATCH_HIERARCHY_CLASS(fma3_, xop_);
#else
  BOOST_DISPATCH_HIERARCHY_CLASS(fma3_, avx_);
#endif
  BOOST_DISPATCH_HIERARCHY_CLASS(avx2_, fma3_);

  // Tag hierarchy for mic extensions
  BOOST_DISPATCH_HIERARCHY_CLASS(mic_, sse2_);
} } }

#endif
