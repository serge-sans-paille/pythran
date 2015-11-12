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
#ifndef NT2_COMPLEX_CONSTANTS_I_HPP_INCLUDED
#define NT2_COMPLEX_CONSTANTS_I_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <complex>

/*!
 * \ingroup nt2_complex
 * \defgroup nt2_complex_i I
 *
 * \par Description
 * Constant I : Imag unit.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/i.hpp>
 * \endcode
 *
 * \alias:
 *    J
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T>
 *     meta::call<tag::I(as_<T>)>::type
 *     I();
 * }
 * \endcode
 *
 *
 * \param T template parameter of I
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag I of functor I
     *        in namespace nt2::tag for toolbox complex
    **/
    struct I : ext::constant_<I>
    {
      typedef std::complex<double> default_type;
      typedef ext::constant_<I> parent;
    };
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::I, I)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::I, J)
}

#endif
