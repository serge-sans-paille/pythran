//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DIV_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DIV_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-oerator
    Function object extending divides

    Calculate the quotient of the two parameters of the same type with or without options.

    @par Semantic

    For any value @c a and @c b of type @c T,

    @code
    T r = div({option, }a, b);
    @endcode

    returns the quotient of @c a by @c b respecting to the options specified.

    By default, this functions is equivalent to divides(a, b).
    Options may be ceil, floor, fix, round, nearbyint (in the namespace booost::simd)
    and provide the same result as the calls divceil(a, b), divfloor(a, b),
    divfix(a, b), divround(a, b), divnearbyint(a, b).

    @return The quotient of the two parameters.
  **/
  T div(T const& a, T const& b);

  //@overload
  T div(Option const& o, T const& a, T const& b);

} }
#endif

#include <boost/simd/function/scalar/div.hpp>
#include <boost/simd/function/simd/div.hpp>


#endif
