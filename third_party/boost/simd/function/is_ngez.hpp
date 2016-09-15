//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NGEZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NGEZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_ngez capabilities

    Returns @ref True if x is not greater or equal to @ref Zero else returns @ref False.

    @par Semantic:

    @code
    auto r = is_ngez(x);
    @endcode

    is similar to:

    @code
    auto r = !(x >= 0);
    @endcode

    @par Note:

    Due to existence of @ref Nan, this is not equivalent to a call to
    @ref is_ltz for floating types

  **/
  as_logical_t<Value> is_ngez(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_ngez.hpp>
#include <boost/simd/function/simd/is_ngez.hpp>

#endif
