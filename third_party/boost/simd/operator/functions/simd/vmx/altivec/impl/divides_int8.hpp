//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_IMPL_DIVIDES_INT8_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_IMPL_DIVIDES_INT8_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  //////////////////////////////////////////////////////////////////////////////
  // a/b use a bit preserving algorithm from vecLib by Apple
  //////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divides_, boost::simd::tag::vmx_, (A0)(A1)
                            , ((simd_<ints8_<A0>,boost::simd::tag::vmx_>))
                              ((simd_<ints8_<A1>,boost::simd::tag::vmx_>)) )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
    }
  };
} } }

#endif
#endif
