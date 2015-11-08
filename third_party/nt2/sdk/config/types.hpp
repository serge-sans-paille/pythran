//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONFIG_TYPES_HPP_INCLUDED
#define NT2_SDK_CONFIG_TYPES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Types injection into nt2
// Injects or define some basic types in NT2 namespace for consistency sake.
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/types.hpp>

namespace nt2
{
  using boost::simd::uint8_t;
  using boost::simd::uint16_t;
  using boost::simd::uint32_t;
  using boost::simd::uint64_t;
  using boost::simd::int8_t;
  using boost::simd::int16_t;
  using boost::simd::int32_t;
  using boost::simd::int64_t;
}

#endif
