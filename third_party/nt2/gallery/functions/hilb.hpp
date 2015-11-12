//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_HILB_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_HILB_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_hilb hilb
 *
 * \par Description
 *   hilb(n) is the n by n matrix with elements 1/(i+j-1),
 *   which is a famous example of a badly conditioned matrix.
 *   see invhilb for the exact inverse.
 *
 *   hilb(n,classname) produces a matrix of class classname.
 *   classname must be either 'single' or 'double' (the default).
 *
 *   this is also a good example of efficient matlab programming
 *   style where conventional for or do loops are replaced by
 *   vectorized statements.  this approach is faster, but uses
 *   more storage.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/hilb.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// hilb actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag hilb_ of functor hilb
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct hilb_ : boost::dispatch::tag::formal_ { typedef boost::dispatch::tag::formal_ parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::hilb_, hilb, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::hilb_, hilb, 2)
  template < class T> container::table<T> hilb(size_t n)
  {
    return nt2::hilb(n, meta::as_<T>());
  }
}
#endif

