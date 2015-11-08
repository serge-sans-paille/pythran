//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_LOTKIN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_LOTKIN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_lotkin lotkin
 *
 *    a = lotkin(n) is the hilbert matrix with its first row
 *    altered to all ones.  a is unsymmetric, ill-conditioned, and has
 *    many negative eigenvalues of small magnitude. its inverse has
 *    integer entries and is known explicitly.
 *
 *    Reference:
 *    M. Lotkin, A set of test matrices, M.T.A.C., 9 (1955), pp. 153-161.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lotkin.hpp>
 * \endcode
 *
 **/
//==============================================================================
// lotkin actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag lotkin_ of functor lotkin
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct lotkin_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lotkin_, lotkin, 2)

}

#endif

