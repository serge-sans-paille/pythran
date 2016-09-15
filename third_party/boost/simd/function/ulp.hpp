//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ULP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ULP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing ulp capabilities

    Returns the ulp distance to the nearest (distinct) element of the same type.

    @par Semantic:

    @code
    T r = ulp(x);
    @endcode

    is similar to:

    @code
    T r = min(x-prev(x), next(x)-x)/Eps<T>();
    @endcode

    @par Note
    ulp stands for Unit in the Last Place.

    @see ulpdist, eps, Eps

  **/
  Value ulp(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/ulp.hpp>
#include <boost/simd/function/simd/ulp.hpp>

#endif
