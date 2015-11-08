//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_LOG1P_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_LOG1P_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief log1p generic tag

     Represents the log1p function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct log1p_ : ext::elementwise_<log1p_> { typedef ext::elementwise_<log1p_> parent; };
  }
  /*!
    natural logarithm of 1+a0: \f$\log(1+a_0)\f$
    \par
    result is accurate even for small a0

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = log1p(x);
    @endcode

    is similar to:

    @code
    T0 r = log(1+x);
    @endcode

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log1p_, log1p, 1)
}

#endif

