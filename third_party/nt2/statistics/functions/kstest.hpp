//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_KSTEST_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_KSTEST_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief kstest generic tag

     Represents the kstest function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct kstest_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }
  /*!
    Kolmogorov-Smirnov test

    @par Semantic:

    For every table expressions

    @code
    tie(d, p) = kstest(x, cd);
    @endcode

    compute the ks statistic d  and the significance level p from
    a distribution sample x and the cumulative distribution functor cd.

    @par Note:

      - small value of p means the data is significantly far from the
      distribution

      - kstest can also be called with L-values to receive the results:
      d = kstest(x, cd, p) or  kstest(x, cd, p, d)

    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::kstest_, kstest, 2)
  /// overload
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::kstest_, kstest, (A0 const&)(A1 const&)(A2&),3)
  /// overload
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::kstest_, kstest, (A0 const&)(A1 const&)(A2&)(A2&),3)


}

#endif
