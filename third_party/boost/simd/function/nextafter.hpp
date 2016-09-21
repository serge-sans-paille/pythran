//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_NEXTAFTER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_NEXTAFTER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing nextafter capabilities

    Returns the next element in the y direction.

    @par Semantic:

    @code
    auto r = nextafter(x, y);
    @endcode

    is similar to:

    @code
    if (y >  x)  r = next(x);
    else if (y == x)  r = x;
    else if (y <  x)  r = prev(x);
    @endcode

    @see next, prev, successor, predecessor

    @par Note:
    C++11 standard library also defines nexttoward, but as (for SIMD consideration)
    x and y must be here of type,  the two function would coincide and nexttoward is not
    defined in boost.simd.

  **/
  Value nextafter(Value const & x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/nextafter.hpp>
#include <boost/simd/function/simd/nextafter.hpp>

#endif
