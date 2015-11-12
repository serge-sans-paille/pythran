//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CROSS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CROSS_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_cross cross
 *
 * \par Description
 * vectors cross  product
 *
 *  c = cross(a,b) returns the cross product of a and b along the
 *  first dimension of common length 3. a and b must share the same size.
 *
 *  c = cross(a,b,dim), where a and b are n-d arrays, returns the cross
 *  product of vectors in the dimension dim of a and b. a and b must
 *  have the same size, and both size(a,dim) and size(b,dim) must be 3.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cross.hpp>
 * \endcode
 *
 *
 * \param a0 a matrix, vector or scalar
 *
 * \param a1 a matrix, vector or scalar
 *
 * \par Notes
 *   Call the dedicated BLAS/LAPACK routines available on the target (DOT, GEMV, GEMM)
 * \par
 *
**/
//==============================================================================
// cross actual class forward declaration
//==============================================================================

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag cross_ of functor cross
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct cross_ :  boost::dispatch::tag::formal_
    {
      typedef  boost::dispatch::tag::formal_ parent;
    };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cross_, cross, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cross_, cross, 3)
}

#endif

