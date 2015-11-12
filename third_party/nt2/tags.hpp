//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TAGS_HPP_INCLUDED
#define NT2_TAGS_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>

namespace nt2
{
  namespace tag
  {
    struct fro_   {};
    struct inf_   {};
    struct two_   {};
    struct one_   {};
    struct minf_  {};
  }

  nt2::meta::as_<tag::fro_>     const fro_ = {};
  nt2::meta::as_<tag::minf_>    const minf_ = {};
  nt2::meta::as_<tag::inf_>     const inf_ = {};
  nt2::meta::as_<tag::one_>     const one_ = {};
  nt2::meta::as_<tag::two_>     const two_ = {};
}

#endif
