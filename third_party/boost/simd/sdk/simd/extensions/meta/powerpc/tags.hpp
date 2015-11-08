//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_POWERPC_TAGS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_POWERPC_TAGS_HPP_INCLUDED

#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/simd/sdk/simd/extensions/meta/common/tags.hpp>

namespace boost { namespace simd { namespace tag
{
  // Tag hierarchy for VMX PPC extensions
  BOOST_DISPATCH_HIERARCHY_CLASS(vmx_, simd_);
  BOOST_DISPATCH_HIERARCHY_CLASS(vsx_, vmx_);

  BOOST_DISPATCH_HIERARCHY_CLASS(qpx_, simd_);
} } }

#endif
