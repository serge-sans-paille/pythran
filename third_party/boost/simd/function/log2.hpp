//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOG2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOG2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing log2 capabilities

    base two logarithm function.

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = log2(x);
    @endcode

    is similar to:

    @code
    T r =  log(x)/log(2);;
    @endcode

    - log2(x) return Nan for negative enties (peculiarly Mzero
    for floating numbers).

    @par Decorators

    std_ for floating entries

    @see log10, log, log1p, is_negative,  Mzero
  **/
  Value log2(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/log2.hpp>
#include <boost/simd/function/simd/log2.hpp>

#endif
