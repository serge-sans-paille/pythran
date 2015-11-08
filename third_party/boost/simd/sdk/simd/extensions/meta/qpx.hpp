//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_QPX_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_QPX_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/simd/meta/is_logical_mask.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>

namespace boost { namespace simd { namespace meta
{
  template<>
  struct is_simd_specific<vector4double, tag::qpx_> : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct as_simd<double, tag::qpx_>
  {
    typedef vector4double type;
  };

  template<>
  struct as_simd<logical<double>, tag::qpx_>
  {
    typedef vector4double type;
  };

  template<>
  struct is_logical_mask< native<logical<double>, tag::qpx_> >
       : boost::mpl::false_
  {
  };

  template<>
  struct extension_of<vector4double> { typedef tag::qpx_ type; };
} } }

#endif
