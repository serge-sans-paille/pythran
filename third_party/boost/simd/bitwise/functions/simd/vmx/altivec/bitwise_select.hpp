//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_SELECT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/bitwise/functions/bitwise_select.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_select_, boost::simd::tag::vmx_
             , (A0)(A1)
             , ((simd_< arithmetic_<A0>, boost::simd::tag::vmx_ >))
               ((simd_< arithmetic_<A1>, boost::simd::tag::vmx_ >))
               ((simd_< arithmetic_<A1>, boost::simd::tag::vmx_ >))
             )
  {
    typedef A1 result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type itype;
      return vec_sel(a2(), a1(), bitwise_cast<itype>(a0)());
    }
  };

} } }

#endif

#endif
