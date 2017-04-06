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
    This function object returns the `n-`th greatest element strictly less than the parameter


    @par Header <boost/simd/function/predecessor.hpp>

    @par Note

     If @c n is null returns @c x else computes the `n`-th greatest representable value strictly less
     than @c x in its type.  @c n must be positive or null.

      - For integer types it saturates at @ref Valmin.

      - For floating point numbers, all @ref Minf  strict predecessors are @ref Nan.

    @see next, prev, successor, nextafter, Minf, Valmin, Nan


    @par Example:

      @snippet predecessor.cpp predecessor

    @par Possible output:

      @snippet predecessor.txt predecessor

  **/
  ///@{
  Value predecessor(Value const& x);
  Value predecessor(Value const& x, IntegerValue const& n);
  ///@}
} }
#endif

#include <boost/simd/function/scalar/predecessor.hpp>
#include <boost/simd/function/simd/predecessor.hpp>

#endif
