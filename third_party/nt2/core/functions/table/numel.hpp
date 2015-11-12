//===========================//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_NUMEL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_NUMEL_HPP_INCLUDED

#include <nt2/core/functions/numel.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0)(S0)(K0)
                            , ((container_<K0,unspecified_<A0>,S0>))
                            )
  {
    typedef typename
            meta::call<tag::numel_(typename A0::extent_type)>::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      return nt2::numel(nt2::extent(a0));
    }
  };
} }

#endif
