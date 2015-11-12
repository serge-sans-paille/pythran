//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_IFVECTVERT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_IFVECTVERT_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/reshaping.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief ifvectvert generic tag

     Represents the ifvectvert function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ifvectvert_ : ext::reshaping_<ifvectvert_>
    {
      /// @brief Parent hierarchy
      typedef ext::reshaping_<ifvectvert_> parent;
    };
  }
  /*!

    Column reshaping if input is vector
    @par Semantic:

    For every parameter of type T0

    @code
    auto r = ifvectvert(a0);
    @endcode

    is similar to:

    @code
    auto r = isvect(a0) ? colvect(a0) : a0;
    @endcode

    @see @funcref{isvect}, @funcref{colvect}
    @param a0

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ifvectvert_       , ifvectvert, 1)
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::ifvectvert_  , ifvectvert, 1)
}

#endif
