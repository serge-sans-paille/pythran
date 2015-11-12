//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_LEHMER_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_LEHMER_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_lehmer lehmer
 *
 * \par Description
 *    lehmer(n, mu) is the (n+1)-by-n matrix
 *    [ones(1,n); mu*eye(n)]. it is a well-known example in
 *    least squares and other problems that indicates the dangers of
 *    forming a'*a. mu defaults to sqrt(eps).

 *    Reference:
 *    P. Lehmer, Jordan-Elimination und Ausgleichung nach
 *    kleinsten Quadraten, Numer. Math, 3 (1961), pp. 226-240.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/lehmer.hpp>
 * \endcode
 *
 **/
//==============================================================================
// lehmer actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag lehmer_ of functor lehmer
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct lehmer_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::lehmer_, lehmer, 2)

  template<class A0>
  typename meta::call<tag::lehmer_(const A0 &, typename meta::as_<double> const &)>::type
  lehmer(const A0& n)
  {
    return nt2::lehmer(n, nt2::meta::as_<double>());
  }
  template<class T, class A0>
  typename meta::call<tag::lehmer_(const A0 &, typename meta::as_<T> const &)>::type
  lehmer(const A0& n)
  {
    return nt2::lehmer(n, nt2::meta::as_<T>());
  }

}

#endif

