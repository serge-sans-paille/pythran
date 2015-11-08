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
#ifndef NT2_COMPLEX_CONSTANTS_SQRTI_HPP_INCLUDED
#define NT2_COMPLEX_CONSTANTS_SQRTI_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <complex>

/*!
 * \ingroup nt2_complex
 * \defgroup nt2_complex_sqrti sqrti
 *
 * \par Description
 * Constant Sqrti : Imag unit principal square root.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/constants/sqrti.hpp>
 * \endcode
 *
 * \alias:
 *    Sqrtj
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T>
 *     meta::call<tag::Sqrti(as_<T>)>::type
 *     Sqrti();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Sqrti
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
     * \brief Define the tag Sqrti of functor Sqrti
     *        in namespace nt2::tag for toolbox complex
    **/
    struct Sqrti : ext::constant_<Sqrti>
    {
      typedef std::complex<double> default_type;
      typedef ext::constant_<Sqrti> parent;
    };
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Sqrti, Sqrti)
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(nt2::tag::Sqrti, Sqrtj)
}

#endif
