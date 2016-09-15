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
    Function object implementing mask2logical capabilities

    The function converts an arithmetic mask where each element is
    Zero or Allbits to a logical value.

    If it is not the case this function asserts.

    @par Semantic:

    @code
    auto r = mask2logical(x);
    @endcode

    is similar to:

    @code
    auto r = (x == Allbits) ? True : (x == Zero) ? False : assert;
    @endcode

  **/
  as_logical_t<Value> mask2logical(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/mask2logical.hpp>
#include <boost/simd/function/simd/mask2logical.hpp>

#endif
