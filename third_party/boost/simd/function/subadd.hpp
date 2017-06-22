//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SUBADD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SUBADD_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    @ingroup swar-subadd

    Alternatively  subtract and add packed  floating-point elements from a pack.
    Scalar version is just minus.

    @par Header <boost/simd/function/subadd.hpp>
    @par Example:

    @snippet subadd.cpp subadd

    @par Possible output:

    @snippet subadd.txt subadd

  **/
} }

#include <boost/simd/function/scalar/subadd.hpp>
#include <boost/simd/function/simd/subadd.hpp>

#endif
