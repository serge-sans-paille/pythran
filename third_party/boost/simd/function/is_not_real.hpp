//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NOT_REAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NOT_REAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_not_real capabilities

    Returns @ref True or @ref False according x is real or not.
    For non complex numbers it is always false

    @par Semantic:

    @code
    auto r = is_not_real(x);
    @endcode

    is similar to:

    @code
    auto r = False;
    @endcode

  **/
  as_logical_t<Value> is_not_real(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_not_real.hpp>
#include <boost/simd/function/scalar/is_not_real.hpp>
#include <boost/simd/function/simd/is_not_real.hpp>

#endif
