//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SUBSPACE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SUBSPACE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_trace trace
 *
 * \par Description
 *  angle between subspaces.
 *    subspace(a,b) finds the angle between two subspaces specified by the
 *    columns of a and b.
 *
 *    References:
 *    [1] A. Bjorck & G. Golub, Numerical methods for computing
 *        angles between linear subspaces, Math. Comp. 27 (1973),
 *        pp. 579-594.
 *    [2] P.-A. Wedin, On angles between subspaces of a finite
 *        dimensional inner product space, in B. Kagstrom & A. Ruhe (Eds.),
 *        Matrix Pencils, Lecture Notes in Mathematics 973, Springer, 1983,
 *        pp. 263-285.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/trace.hpp>
 * \endcode
 *
 *
 * \param a the matrix a
 *
 * \param b the matrix b
 *
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *
**/
//==============================================================================
// trace actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag trace_ of functor trace
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct subspace_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::subspace_, subspace, 2)
}

#endif
