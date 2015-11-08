//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COSECANT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COSECANT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief cosecant generic tag

     Represents the cosecant function in generic contexts.

     @par Models:
        Hierarchy
   **/
    template <class T>
    struct cosecant_ : ext::elementwise_< cosecant_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< cosecant_<T> > parent;
    };
  }
  /*!
    cosecant with template selection.

    @par Semantic:

    For template selector @c Range in proper selector types choice
    and for every parameter of floating type respectively T0:

    @code
    T0 r = cosecant<Range>(x);
    @endcode

    is similar to:

    @code
    T0 r = csc(x);
    @endcode

    but with the limitations and speed-up than can be implied
    by the @c Range choice (see cosine for details)

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cosecant_<A0> , cosecant, (A1 const&), 2)
}

#endif

