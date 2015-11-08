//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_NUMERIC_CLASS_HPP_INCLUDED
#define NT2_CORE_NUMERIC_CLASS_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/config/types.hpp>

namespace nt2
{
  meta::as_<double>        const double_ = {};
  meta::as_<float>         const single_ = {};
  meta::as_<nt2::int64_t>  const int64_  = {};
  meta::as_<nt2::int32_t>  const int32_  = {};
  meta::as_<nt2::int16_t>  const int16_  = {};
  meta::as_<nt2::int8_t>   const int8_   = {};
  meta::as_<nt2::uint64_t> const uint64_ = {};
  meta::as_<nt2::uint32_t> const uint32_ = {};
  meta::as_<nt2::uint16_t> const uint16_ = {};
  meta::as_<nt2::uint8_t>  const uint8_  = {};
}

#endif
