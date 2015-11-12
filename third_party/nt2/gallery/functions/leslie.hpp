//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_LESLIE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_LESLIE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_leslie leslie
 *
 *    leslie(a,b) is the n-by-n matrix from the Leslie
 *    population model with average birth numbers a(_(1, n)) and
 *    survival rates b(_(1, n-1)).  it is zero, apart from on the first row
 *    (which contains the a(i)) and the first subdiagonal (which contains
 *    the b(i)).  for a valid model, the a(i) are nonnegative and the
 *    b(i) are positive and bounded by 1.
 *
 *    leslie(n) generates the leslie matrix with a = ones(n,1),
 *    b = ones(n-1,1).

 *    References:
 *    [1] M. R. Cullen, Linear Models in Biology, Ellis Horwood,
 *        Chichester, UK, 1985.
 *    [2] H. Anton and C. Rorres, Elementary Linear Algebra: Applications
 *        Version, eighth edition, Wiley, New York, 2000, Sec. 11.18.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/leslie.hpp>
 * \endcode
 *
 **/
//==============================================================================
// leslie actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag leslie_ of functor leslie
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct leslie_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::leslie_, leslie, 2)

}

#endif

