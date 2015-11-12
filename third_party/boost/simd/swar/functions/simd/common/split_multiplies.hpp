//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/swar/functions/split_multiplies.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_multiplies_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1, A1& a2, A1& a3) const
    {
      A1 a00, a01, a10, a11;
      split(a0, a00, a01);
      split(a1, a10, a11);
      a2 = a00*a10;
      a3 = a01*a11;
    }
  };
} } }

#endif
