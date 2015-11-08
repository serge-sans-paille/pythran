//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_COV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_COV_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <boost/simd/constant/constants/zero.hpp>


namespace nt2 {  namespace tag
  {
    /*!
     * \brief Define the tag expm_ of functor expm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct cov_ : tag::formal_
    {
       typedef tag::formal_ parent;
    };
  }
  /**
   * @brief compute covariance matrix expression
   *
   * If x is a vector,  cov(x) returns the variance
   * For matrices, where each row is an observation, and each column a variable,
   * cov(x) is the covariance matrix.  diag(cov(x)) is a vector of
   * variances for each column, and sqrt(diag(cov(x))) is a vector
   * of standard deviations.
   * cov(x,y), where x and y are matrices with the same number of elements,
   * is equivalent to cov(horzcat(x(_) y(_))).
   *
   * cov(x) or cov(x,y) normalizes by (n-1) if n>1, where n is the number of
   * observations.  this makes cov(x) the best unbiased estimate of the
   * covariance matrix if the observations are from a normal distribution.
   * for n=1, cov normalizes by n.
   *
   *  cov(x,1) or cov(x,y,1) normalizes by n and produces the second
   * moment matrix of the observations about their mean.  cov(x,y,0) is
   * the same as cov(x,y) and cov(x,0) is the same as cov(x).
   *
   * the mean is removed from each column before calculating the
   * result.
   *
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cov_       , cov, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cov_       , cov, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::cov_       , cov, 3)
}

#endif
