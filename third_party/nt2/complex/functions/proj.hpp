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
#ifndef NT2_COMPLEX_FUNCTIONS_PROJ_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_PROJ_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup nt2_complex
 * \defgroup nt2_complex_proj proj
 *
 * \par Description
 * return the proj part of a complex
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/proj.hpp>
 * \endcode
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *     template <class A0>
 *     meta::call<tag::proj_(A0)>::type
 *     nt2::proj(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the first parameter of proj
 *
 * \return a proj value
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
     * \brief Define the tag proj_ of functor proj
     *        in namespace nt2::tag for toolbox complex
    **/
    struct proj_ : ext::elementwise_<proj_> { typedef ext::elementwise_<proj_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::proj_, proj, 1)
}

#endif
