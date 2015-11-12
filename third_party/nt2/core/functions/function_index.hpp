//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FUNCTION_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FUNCTION_INDEX_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/simd/category.hpp>

namespace nt2
{
  namespace tag
  {
    struct function_index_ : ext::elementwise_<function_index_>
    {
      typedef ext::elementwise_<function_index_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::function_index_, function_index, 3)
}

#endif
