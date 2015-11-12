//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_COMPLEX_FUNCTIONS_TOCOMPLEX_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_TOCOMPLEX_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup nt2_complex
 * \defgroup nt2_complex_tocomplex tocomplex
 *
 * \par Description
 * return a complex constructed from the parameter(s)
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tocomplex.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::tocomplex_(A0)>::type
 *     tocomplex(const A0 & a0);
 *   template <class A0>
 *     meta::call<tag::tocomplex_(A0, A0)>::type
 *     tocomplex(const A0 & a0, const A0& a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of tocomplex
 * \param a1 the second parameter of tocomplex
 *
 * \return a real value
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the input vectors' elements
 * \par
 *
**/

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag tocomplex_ of functor tocomplex
     *        in namespace nt2::tag for toolbox complex
    **/
    struct tocomplex_ : ext::elementwise_<tocomplex_> { typedef ext::elementwise_<tocomplex_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tocomplex_, tocomplex, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::tocomplex_, tocomplex, 2)
}

#endif
