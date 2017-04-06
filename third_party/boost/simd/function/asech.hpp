//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASECH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASECH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function returns the hyperbolic secant argument \f$\mathop{\textrm{acosh}}(1/x)\f$

    @par Header <boost/simd/function/asech.hpp>

    @see cosh, acosh, sinh, asinh, atanh, atanh, acoth, acsch

    @par Example:

      @snippet asech.cpp asech

    @par Possible output:

      @snippet asech.txt asech

  **/
  IEEEValue asech(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/asech.hpp>
#include <boost/simd/function/simd/asech.hpp>

#endif
