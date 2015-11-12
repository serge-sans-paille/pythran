//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_EXPONENTIAL_FUNCTIONS_EXPI_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_EXPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup expionential
 * \defgroup expionential_expi expi
 *
 * \par Description
 * expionential function: \f$e^{ia_0}\f$ where  \f$i^{2} = -1\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/expi.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expi_(A0)>::type
 *     expi(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of expi
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag expi_ of functor expi
     *        in namespace nt2::tag for toolbox expionential
    **/
    struct expi_ : ext::elementwise_<expi_> { typedef ext::elementwise_<expi_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expi_, expi, 1)
}

#endif
