//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_INDEG_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_INDEG_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief indeg generic tag

     Represents the indeg function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct indeg_ : ext::elementwise_<indeg_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<indeg_> parent;
    };
  }
  /*!
    convert radian to degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = indeg(x);
    @endcode

    is similar to:

    @code
    T0 r = Radindeg<T0>()*x;
    @endcode

    @see  @funcref{inrad}, @funcref{Radindeg}, @funcref{Radindegr}, @funcref{Deginrad}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::indeg_, indeg, 1)
}

#endif


