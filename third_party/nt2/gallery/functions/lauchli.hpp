//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_LAUCHLI_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_LAUCHLI_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_lauchli lauchli
 *
 * \par Description
 *    lauchli(n, mu) is the (n+1)-by-n matrix
 *    [ones(1,n); mu*eye(n)]. it is a well-known example in
 *    least squares and other problems that indicates the dangers of
 *    forming a'*a. mu defaults to sqrt(eps).

 *    Reference:
 *    P. Lauchli, Jordan-Elimination und Ausgleichung nach
 *    kleinsten Quadraten, Numer. Math, 3 (1961), pp. 226-240.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lauchli.hpp>
 * \endcode
 *
 **/
//==============================================================================
// lauchli actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag lauchli_ of functor lauchli
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct lauchli_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lauchli_, lauchli, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lauchli_, lauchli, 2)

  template<class T, class A0>
  typename meta::call<tag::lauchli_(const A0 &, typename meta::as_<T> const &)>::type
  lauchli(const A0& n)
  {
    return nt2::lauchli(n, meta::as_<T>());
  }
}

#endif

