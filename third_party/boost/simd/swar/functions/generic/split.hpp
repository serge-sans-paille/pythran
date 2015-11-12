//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_GENERIC_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_GENERIC_SPLIT_HPP_INCLUDED

#include <boost/simd/swar/functions/split.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_
                                      , tag::cpu_
                                      , (A0)(A1)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((generic_< unspecified_<A0> >))
                                        ((generic_< unspecified_<A1> >))
                                      )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 & a2) const
    {
      result_type a1;
      boost::simd::split(a0, a1, a2);
      return a1;
    }
  };
} } }

#endif
