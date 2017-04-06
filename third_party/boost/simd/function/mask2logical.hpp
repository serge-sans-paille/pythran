//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MASK2LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MASK2LOGICAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object converts
    an arithmetic mask where each element is
    Zero or Allbits to a logical value.

    If it is not the case this function asserts.


    @par Header <boost/simd/function/mask2logical.hpp>

    @par Example:

      @snippet mask2logical.cpp mask2logical

    @par Possible output:

      @snippet mask2logical.txt mask2logical

  **/
  as_logical_t<Value> mask2logical(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/mask2logical.hpp>
#include <boost/simd/function/simd/mask2logical.hpp>

#endif
