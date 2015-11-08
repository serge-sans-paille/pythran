//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_DIVIDES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

////////////////////////////////////////////////////////////////////////////////
// Altivec division algorithm are long-ass. Let's hide them for clarity purpose
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/operator/functions/divides.hpp>
#include <boost/simd/operator/functions/simd/vmx/altivec/impl/divides_float.hpp>
//#include <boost/simd/operator/functions/simd/vmx/altivec/impl/divides_int32.hpp>
//#include <boost/simd/operator/functions/simd/vmx/altivec/impl/divides_int16.hpp>
//#include <boost/simd/operator/functions/simd/vmx/altivec/impl/divides_int8.hpp>

#endif
#endif
