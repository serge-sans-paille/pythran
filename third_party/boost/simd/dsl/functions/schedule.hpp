//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_SCHEDULE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_SCHEDULE_HPP_INCLUDED

#include <boost/dispatch/functor/preprocessor/function.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct schedule_ : dispatch::tag::formal_ { typedef dispatch::tag::formal_ parent; };
    struct schedule_assign_ : dispatch::tag::formal_ { typedef dispatch::tag::formal_ parent; };
  }

  // Tree + function + top mark
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_, schedule, (A0&)(A1 const&), 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_, schedule, (A0 const&)(A1 const&), 2)

  // Special case assign node
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0 const&)(A1&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0 const&)(A1 const&)(A2 const&), 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::schedule_assign_, schedule_assign, (A0&)(A1 const&)(A2 const&), 3)
} }

#endif
