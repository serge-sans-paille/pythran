//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_PEI_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_PEI_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_pei pei
 *
 *    pei(n,alpha), where alpha is a scalar, is the symmetric
 *    matrix alpha*eye(n) + ones(n). the default for alpha is 1.
 *    the matrix is singular for alpha = 0, -n.
 *
 *    Reference:
 *    M. L. Pei, A test matrix for inversion procedures, Comm. ACM,
 *    5 (1962), p. 508.
 *
! * \par Header file
 *
 * \code
 * #include <nt2/include/functions/pei.hpp>
 * \endcode
 *
 **/
//==============================================================================
// pei actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag pei_ of functor pei
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct pei_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::pei_, pei, 2)

}

#endif

