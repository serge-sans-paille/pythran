//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_EYEMINUS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_EYEMINUS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
      struct eyeminus_ :  boost::dispatch::tag::formal_
      {
        typedef boost::dispatch::tag::formal_ parent;
      };
  }

  /**
   * @brief Perform eyeminus(a, l)computation
   *
   * For any given matrix expression computes eye(right_size,  right_type) - a*l .
   * l defaults to 1.
   *
   * @param    a Matrix expression to factorize
   * @param    l scalar factor to apply to a
   *
   * @return an expression for the result
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::eyeminus_, eyeminus, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::eyeminus_, eyeminus, 2)

}

#endif
