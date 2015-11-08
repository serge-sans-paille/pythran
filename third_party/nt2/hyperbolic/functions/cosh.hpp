//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COSH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief cosh generic tag

     Represents the cosh function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct cosh_ : ext::elementwise_<cosh_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<cosh_> parent;
    };
  }
  /*!
    Returns the hyperbolic cosine: \f$\frac{e^{a_0}+e^{-a_0}}2\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = cosh(x);
    @endcode

    is similar to:

    @code
    T0 r = Half<T0>()*(exp(x)+exp(-x));
    @endcode

    @see @funcref{exp}, @funcref{sinh}, @funcref{Half}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cosh_, cosh, 1)
}

#endif

