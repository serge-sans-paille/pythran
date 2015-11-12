//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COTANGENT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COTANGENT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief cotangent generic tag

     Represents the cotangent function in generic contexts.

     @par Models:
        Hierarchy
   **/
    template <class T>
    struct cotangent_ : ext::elementwise_< cotangent_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< cotangent_<T> > parent;
    };
  }
  /*!
    cotangent with template selection.

    @par Semantic:

    For template selector @c Range in proper selector types choice
    and for every parameter of floating type T0:

    @code
    T0 r = cotangent<Range>(x);
    @endcode

    is similar to:

    @code
    T0 r = cosine<Range>(x)/sine<Range>(x);
    @endcode

    @see @funcref{cot}, @funcref{fast_cot}, @funcref{cotd}, @funcref{cotpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cotangent_<A0> , cotangent, (A1 const&), 2)
}

#endif


