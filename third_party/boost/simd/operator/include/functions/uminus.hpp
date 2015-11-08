//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_INCLUDE_FUNCTIONS_UMINUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_INCLUDE_FUNCTIONS_UMINUS_HPP_INCLUDED
#include <boost/simd/operator/include/functions/unary_minus.hpp>

namespace boost { namespace simd { namespace tag
{
  typedef unary_minus_ uminus_;
} } }

namespace boost { namespace simd
{
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::uminus_, uminus, 1)
} }
#endif
