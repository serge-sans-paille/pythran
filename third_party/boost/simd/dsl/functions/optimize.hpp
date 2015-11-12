//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_OPTIMIZE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_OPTIMIZE_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/function.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>

namespace boost { namespace simd
{
  namespace tag { struct optimize_ : dispatch::tag::formal_ { typedef dispatch::tag::formal_ parent; }; }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::optimize_, optimize, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::optimize_, optimize, (A0&), 1)
} }

#endif
