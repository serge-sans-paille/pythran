//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-hyperbolic
    Function object implementing sinh capabilities

    Returns the hyperbolic sine: \f$(e^{x}-e^{-x})/2\f$.

    @par Semantic:

    For every parameter of floating type @c T

    @code
    T r = sinh(x);
    @endcode

    @see exp, cosh, sinhcosh

  **/
  Value sinh(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sinh.hpp>
#include <boost/simd/function/simd/sinh.hpp>

#endif
