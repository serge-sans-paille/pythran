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
    Returns the next representable value of @c x in the direction of @c y


    @par Header <boost/simd/function/nextafter.hpp>

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

    @par Note
    C++11 standard library also defines @c nexttoward, but as (for SIMD considerations)
    @c x and @c y must be here of same type, the two function would coincide.
    So @c nexttoward is not defined in boost.simd.

    @par Decorators

     - std_ calls std::nextafter


    @par Example:

      @snippet nextafter.cpp nextafter

    @par Possible output:

      @snippet nextafter.txt nextafter

  **/
  Value nextafter(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/nextafter.hpp>
#include <boost/simd/function/simd/nextafter.hpp>

#endif
