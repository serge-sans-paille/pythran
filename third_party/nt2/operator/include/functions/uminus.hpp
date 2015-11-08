//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_INCLUDE_FUNCTIONS_UMINUS_HPP_INCLUDED
#define NT2_OPERATOR_INCLUDE_FUNCTIONS_UMINUS_HPP_INCLUDED
#include <nt2/operator/include/functions/unary_minus.hpp>

namespace nt2 { namespace tag
{
  typedef unary_minus_ uminus_;
} }

namespace nt2
{
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::uminus_, uminus, 1)
}
#endif
