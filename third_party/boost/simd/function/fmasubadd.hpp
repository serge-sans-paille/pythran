//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FMASUBADD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FMASUBADD_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    @ingroup swar-fmasubadd

    Computes the interleaved sum/difference of two the product of two values with a
    third one

    @par Header <boost/simd/function/fmasubadd.hpp>
    @par Example:

    @snippet fmasubadd.cpp fmasubadd

    @par Possible output:

    @snippet fmasubadd.txt fmasubadd

  **/
} }

#include <boost/simd/function/scalar/fmasubadd.hpp>
#include <boost/simd/function/simd/fmasubadd.hpp>

#endif
