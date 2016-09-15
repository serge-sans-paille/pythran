//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_GEZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_GEZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_gez capabilities

    Returns @ref True or @ref False according x is greater or equal to @ref Zero or not.

    @par Semantic:

    @code
    auto r = is_gez(x);
    @endcode

    is similar to:

    @code
    auto r = x >= Zero;
    @endcode

  **/
  as_logical_t<Value> is_gez(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_gez.hpp>
#include <boost/simd/function/simd/is_gez.hpp>

#endif
