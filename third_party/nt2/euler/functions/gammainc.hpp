//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_GAMMAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_GAMMAINC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief gammainc generic tag

     Represents the gammainc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct gammainc_ : ext::elementwise_<gammainc_>
    {
      typedef ext::elementwise_<gammainc_> parent;
    };
  }

  /*!
    @brief Incomplete Gamma function

    Computes the incomplete gamma function.

    @par Semantic:

    For any floating-point values @c a0 , @c a1 of type T:

    @code
    T r = gammainc(a0,a1);
    @endcode

    returns the value computed by the formula:

    \f$ gammainc(x)=\int_0^{a_1} t^{a_0-1}e^{-t}dt\f

    @param a0 Lower bound of the incomplete gamma integral
    @param a1 Upper bound of the incomplete gamma integral

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gammainc_, gammainc, 2)
}

#endif

