//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HIGH_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HIGH_HPP_INCLUDED

#include <boost/simd/swar/functions/split_high.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/preprocessor/make.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_high_
                                      , tag::cpu_
                                      , (A0)(X)
                                      , (simd::meta::is_upgradable<A0>)
                                      , ((simd_<arithmetic_<A0>,X>))
                                      )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;
    typedef typename meta::scalar_of<result_type>::type sA1;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return eval(a0,typename simd::meta::cardinal_of<result_type>::type());
    }

    #define M0(z, n, t) static_cast<sA1>(extract<n+t>(a0))

    BOOST_SIMD_PP_IMPLEMENT_WITH_MAKE(1, M0)

    #undef M0
  };
} } }

#endif
