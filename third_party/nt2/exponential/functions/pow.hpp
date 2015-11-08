//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_POW_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief pow generic tag

     Represents the pow function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct pow_ : ext::elementwise_<pow_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<pow_> parent;
    };
  }
  /*!
    Computes a0 to a1

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = pow(x,y);
    @endcode

    is similar to:

    @code
    T0 r = exp(y*log(x));
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::pow_, pow, 2)
}

#endif

