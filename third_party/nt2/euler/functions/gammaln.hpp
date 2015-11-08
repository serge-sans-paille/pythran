//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_GAMMALN_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_GAMMALN_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief gammaln generic tag

     Represents the gammaln function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct gammaln_ : ext::elementwise_<gammaln_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<gammaln_> parent;
    };
  }
  /*!
    Natural logarithm of the absolute value of the Gamma function

    Note that the accuracy is not uniformly good for negative entries
    The algorithm used is currently an adapted vesion of the cephes one.
    For better accuracy in the negative entry case one can use the extern
    boost_math gammaln functor but at a loss of speed.
    However,  as stated in boost math:
      "While the relative errors near the positive roots of lgamma are very low,
       the  function has an infinite number of irrational roots for negative arguments:
       very close to these negative roots only a low absolute error can be guaranteed."

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = gammaln(x);
    @endcode

    is similar to:

    @code
    T0 r = log(gamma(abs(x)));
    @endcode

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gammaln_, gammaln, 1)
}

#endif

