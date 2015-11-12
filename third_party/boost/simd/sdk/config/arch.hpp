//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_ARCH_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_ARCH_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for architecture related variation point.
// Documentation: http://nt2.lri.fr/sdk/config/architecture.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/version.hpp>

////////////////////////////////////////////////////////////////////////////////
// Include custom specific architectures from extensions folders
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/arch/powerpc.hpp>
#include <boost/simd/sdk/config/arch/x86.hpp>
#include <boost/simd/sdk/config/arch/ia64.hpp>
#include <boost/simd/sdk/config/arch/arm.hpp>
#include <boost/simd/sdk/config/arch/none.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some other architecture specific informations
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/arch/stack.hpp>
//#include <boost/simd/support/config/arch/endian.hpp>

#endif
