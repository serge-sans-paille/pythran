//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing dot capabilities

    returns the dot product of the two vector arguments

    @par Semantic:

    For every parameters of type T:

    @code
    scalar_of_t<T> r = dot(x,y);
    @endcode

    is similar to:

    @code
    scalar_of_t<T> r = sum(x*conj(y));
    @endcode

  **/
  scalar_of_t<Value> dot(Value const & v0, Value const& v1);
} }
#endif

#include <boost/simd/function/scalar/dot.hpp>
#include <boost/simd/function/simd/dot.hpp>

#endif
