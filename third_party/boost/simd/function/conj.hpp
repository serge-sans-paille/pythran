//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CONJ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CONJ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    function object computes the complex conjugate of its parameter

    @par Header <boost/simd/function/conj.hpp>

    @par Notes

    - for real entries it resumes to the identity

  **/
  Value conj(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/conj.hpp>
#include <boost/simd/function/simd/conj.hpp>

#endif
