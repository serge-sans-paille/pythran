//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SECANT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SECANT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief secant generic tag

     Represents the secant function in generic contexts.

     @par Models:
        Hierarchy
   **/
    template <class T> struct secant_ : ext::elementwise_< secant_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< secant_<T> > parent;
    };
  }
  /*!
    TODO Put description here

    @par Semantic:

    For every parameters of floating types respectively T0:

    @code
    T0 r = secant<Range>(x);
    @endcode

    is similar to:

    @code
    T0 r = secant(x);
    @endcode

    but with the limitations and speed-up than can be implied
    by the @c Range choice (see cosine for details)

    @see @funcref{secd}, @funcref{secpi}, @funcref{sec},
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::secant_<A0> , secant, (A1 const&), 2)
}

#endif


