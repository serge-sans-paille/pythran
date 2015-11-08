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
#ifndef NT2_COMPLEX_FUNCTIONS_REAL_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_REAL_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup nt2_complex
 * \defgroup nt2_complex_real real
 *
 * \par Description
 * return the real part of a complex
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/real.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *     template <class A0>
 *     meta::call<tag::real_(A0)>::type
 *     nt2::real(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of real
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
     * \brief Define the tag real_ of functor real
     *        in namespace nt2::tag for toolbox complex
    **/
    struct real_ : ext::elementwise_<real_> { typedef ext::elementwise_<real_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::real_, real, 1)
}

#endif
