//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_PREDECESSOR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_PREDECESSOR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing predecessor capabilities

    Returns the n-th greatest element strictly less than the parameter

    @par Semantic:

    @code
    auto r = predecessor(x,n);
    @endcode

    If n is null returns x else computes the n-th greatest representable value strictly less than x in its type.
    n must be positive or null.

    For integer it saturate at @ref Valmin. For floating point numbers, all @ref Minf
    strict predecessors are @ref Nan.

    @see next, prev, successor, nextafter, Minf, Valmin, Nan

  **/
  Value predecessor(Value const & v0, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/predecessor.hpp>
#include <boost/simd/function/simd/predecessor.hpp>

#endif
