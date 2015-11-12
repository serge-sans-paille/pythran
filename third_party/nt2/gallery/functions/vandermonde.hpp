//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_VANDERMONDE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_VANDERMONDE_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_vandermonde vandermonde
 *
 * \par Description
 * vandermonde matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/vandermonde.hpp>
 * \endcode
 *
 *
 * \param x the fundamental column of the matrix,
 *        x is always treated as a big column vector
 *
 * \param n (optinnal) the number of column of the matrix (default is numel(x(_))
 *
**/
//==============================================================================
// vandermonde actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag vandermonde_ of functor vandermonde
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct vandermonde_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::vandermonde_, vandermonde, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::vandermonde_, vandermonde, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::vandermonde_, vander, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::vandermonde_, vander, 1)
}

#endif
