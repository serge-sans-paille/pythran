//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPX2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPX2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing expx2 capabilities

    exponential of square function: \f$e^{x^2}\f$ or \f$e^{-x^2}\f$

    @par Semantic:

    For every parameters of floating type T

    @code
    T r = expx2(x, s);
    @endcode

    is similar to:

    @code
    T r =  exp(signnz(s)*x*x);
    @endcode

    @par Note:
    provisions are made for obtaining more accurate results for large x.
    s default to 1.

    @see exp

  **/
  Value expx2(Value const & x, Value const& s);
} }
#endif

#include <boost/simd/function/scalar/expx2.hpp>
#include <boost/simd/function/simd/expx2.hpp>

#endif
