//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINHC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINHC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-hyperbolic
    Function object implementing sinhc capabilities

    Returns hyperbolic cardinal sine: \f$\sinh(x)/x\f$.

    @par Semantic:

    For every parameter of floating type @c T

    @code
    T r = sinhc(x);
    @endcode

    @see sinh

  **/
  Value sinhc(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sinhc.hpp>
#include <boost/simd/function/simd/sinhc.hpp>

#endif
