//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_ELLPK_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_ELLPK_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief ellpk generic tag

     Represents the ellpk function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ellpk_ : ext::elementwise_<ellpk_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ellpk_> parent;
    };
  }
  /*!
    Complete elliptic integral of the first kind

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = ellpk(a0);
    @endcode

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::ellpk_, ellpk, 1)
}

#endif

