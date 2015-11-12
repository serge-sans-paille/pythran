//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_TANGENT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_TANGENT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief tangent generic tag

     Represents the tangent function in generic contexts.

     @par Models:
        Hierarchy
   **/
    template <class T> struct tangent_ : ext::elementwise_< tangent_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< tangent_<T> > parent;
    };
  }
  /*!
    tangent.

    @par Semantic:

    For template selector @c Range in proper selector types choice
    and for every parameter of floating type  T0:

    @code
    T0 r = tangent<Range>(x);
    @endcode

    is similar to:

    @code
    T0 r =  sine<Range>(x)/cosine<Range>(x);;
    @endcode

    @see @funcref{fast_tan}, @funcref{tan}, @funcref{tand}, @funcref{tanpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::tangent_<A0> , tangent, (A1 const&), 2)
}

#endif

