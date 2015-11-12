//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_VECNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_VECNORM_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_vecnorm vecnorm
 *
 * \par Description
 * norm of a vector
 *
 * vecnorm(v) is the same as vecnorm(v,2).
 * vecnorm(v,p) returns the p-norm of v defined as sum(abs(v).^p)^(1/p).
 * vecnorm(v,inf) returns the largest element of abs(v).
 * vecnorm(v,-inf) returns the smallest element of abs(v).
 * by convention, nan is returned if x or v contains nans.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/vecnorm.hpp>
 * \endcode
 *
 *
 * \param v the expresion vector, even if matricial it is always considered as a
 *          big column vector
 *
 * \param the type of norm required
 *
 *

 * \par Notes
 *   Call norm to obtain the Matlab behaviour on matrices.
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag vecnorm_ of functor vecnorm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct vecnorm_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::vecnorm_, vecnorm, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(nt2::tag::vecnorm_, vecnorm, 2)
}

#endif
