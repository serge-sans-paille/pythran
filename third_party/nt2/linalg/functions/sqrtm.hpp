//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SQRTM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SQRTM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_sqrtm sqrtm
 *
 * \par Description
 * suqre root of a matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrtm.hpp>
 * \endcode
 *
 *
 * \param a the matrix or vector expression a
 *
 * \param type of sqrtm required
 *
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag sqrtm_ of functor sqrt
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct sqrtm_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sqrtm_, sqrtm, 1)
}

#endif
