//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_ANP_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_ANP_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief anp generic tag

     Represents the anp function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct anp_ : ext::elementwise_<anp_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<anp_> parent;
    };
  }
  /*!
    Computes the number of arrangement of p elements among n
    If a0 (n) and a1 (p) are not of integer type
    they are rounded to nearest integer before computation.
    \par Formula
    \f[A_n^p = \frac{n!}{(n-p)!}\f]

    @par Semantic:

    For every table expressions n and p

    @code
    auto r = anp(n, p);
    @endcode

    is similar to:

    @code
    auto r = exp(gammaln(n+1)-gammaln(n-p+1));
    @endcode

    @see @funcref{exp},  @funcref{gammaln},  @funcref{cnp}
    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::anp_, anp, 2)
}

#endif

