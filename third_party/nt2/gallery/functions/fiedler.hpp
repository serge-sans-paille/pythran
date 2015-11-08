//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_FIEDLER_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_FIEDLER_HPP_INCLUDED
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_fiedler fiedler
 *
 * \par Description
 *  Fiedler fiedler matrix.
 *   a = fiedler(c), where c is an n-vector, is the n-by-n
 *   symmetric matrix with elements abs(c(i)-c(j)). if c is a scalar,
 *   then a = fiedler(_(1, c)).
 *
 *   a has a dominant positive eigenvalue and all the other eigenvalues
 *   are negative. (szego 1936)
 *
 *   note: explicit formulas for inv(a) and det(a) are given in (todd 1977)
 *   and attributed to fiedler. these indicate that inv(a) is
 *   tridiagonal except for nonzero (1,n) and (n,1) elements.
 *
 *   references:
 *     [1] g. szego, solution to problem 3705, amer. math. monthly,
 *       43 (1936), pp. 246-259.
 *     [2] j. todd, basic numerical mathematics, vol. 2: numerical algebra,
 *       birkhauser, basel, and academic press, new york, 1977, p. 159.
 *
 *   Copyright 1984-2002 The MathWorks, Inc.
 *   $Revision: 1.11 $  $Date: 2002/04/15 03:42:11 $
 *
 * \code
 * #include <nt2/include/functions/fiedler.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// fiedler actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag fiedler_ of functor fiedler
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct fiedler_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::fiedler_, fiedler, 1)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::fiedler_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::fiedler_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};

} }

#endif
