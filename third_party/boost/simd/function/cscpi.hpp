//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CSCPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CSCPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the cosecant of angle in
    \f$\pi\f$ multiples: \f$1/c\sin(\pi x)\f$.


    @par Header <boost/simd/function/cscpi.hpp>

    @par Note

      As most other trigonometric function cscpi can be called with
      a second optional parameter  which is a tag on speed and accuracy
      (see @ref cos for further details)

    @see cscd, csc,


    @par Example:

      @snippet cscpi.cpp cscpi

    @par Possible output:

      @snippet cscpi.txt cscpi

  **/
  IEEEValue cscpi(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/cscpi.hpp>
#include <boost/simd/function/simd/cscpi.hpp>

#endif
