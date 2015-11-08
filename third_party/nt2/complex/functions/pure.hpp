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
#ifndef NT2_COMPLEX_FUNCTIONS_PURE_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_PURE_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup nt2_complex
 * \defgroup nt2_complex_pure pure
 *
 * \par Description
 * return the pure imag part of a complex
 * but as a value of complex type
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/pure.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::pure_(A0)>::type
 *     pure(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of pure
 *
 * \return a complex value
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
     * \brief Define the tag pure_ of functor pure
     *        in namespace nt2::tag for toolbox complex
    **/
    struct pure_ : ext::elementwise_<pure_> { typedef ext::elementwise_<pure_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::pure_, pure, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::pure_, c_imag, 1)
}

#endif
