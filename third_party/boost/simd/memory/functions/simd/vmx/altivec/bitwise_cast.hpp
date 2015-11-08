//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_CAST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::vmx_
                                   , (A0)(A1)
                                   , ((simd_< arithmetic_<A0>, boost::simd::tag::vmx_ >))
                                     ((target_< simd_< arithmetic_<A1>, boost::simd::tag::vmx_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return (typename result_type::native_type)a0();
    }
  };
} } }

#endif
#endif
