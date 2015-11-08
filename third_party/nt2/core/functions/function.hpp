//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FUNCTION_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  namespace tag
  {
    struct function_ : ext::elementwise_<function_>
    {
      typedef ext::elementwise_<function_> parent;
    };
  }

  //============================================================================
  // Generate all calls from function(lhs) to function(lhs, i0, ..., in)
  // with both const and non const lhs variant
  //============================================================================
  #define M0(z, n, t)                                                 \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::function_, function, n)       \
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::function_, function, n)  \
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::function_, at, n)             \
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::function_, at, n)        \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M0
}

#include <nt2/core/functions/details/function.hpp>

#endif
