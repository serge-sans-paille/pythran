//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_FORSYTHE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_FORSYTHE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrteps.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_forsythe forsythe
 *
 * \par Description
 * forsythe forsythe matrix (perturbed jordan block).
 *    a = forsythe(n,alpha,lambda) is the n-by-n matrix
 *    equal to the jordan block with eigenvalue lambda with the
 *    exception that a(n,1) = alpha.
 *    alpha defaults to sqrt(eps) and lambda to 0.
 *
 *    the characteristic polynomial of a is given by
 *       det(a-t*In) = (lambda-t)^n - alpha*(-1)^n.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/forsythe.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// forsythe actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag forsythe_ of functor forsythe
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct forsythe_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::forsythe_, forsythe, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::forsythe_, forsythe, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::forsythe_, forsythe, 4)

  template<class T, class A0>
  typename meta::call<tag::forsythe_(const A0 &,  typename meta::as_<T>::type const &)>::type
  forsythe(const A0& n)
  {
    return nt2::forsythe(n, nt2::meta::as_<T>());
  }
  template<class T, class A0, class A1>
  typename meta::call<tag::forsythe_(const A0 &, const A1&,  typename meta::as_<T>::type const &)>::type
  forsythe(const A0& n, const A1& alpha)
  {
    return nt2::forsythe(n, alpha, nt2::meta::as_<T>());
  }
  template<class T, class A0, class A1,  class A2>
  typename meta::call<tag::forsythe_(const A0 &, const A1&, const A2&, typename meta::as_<T>::type const &)>::type
  forsythe(const A0& n, const A1& alpha, const A2& lambda)
  {
    return nt2::forsythe(n,alpha, lambda,nt2::meta::as_<T>());
  }

}

#endif
