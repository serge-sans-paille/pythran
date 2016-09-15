//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TOINT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TOINT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing toint capabilities

    Convert to integer by truncation.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T> r = toint(x);
    @endcode

    The code is similar to:

    @code
    as_integer_t<T> r = static_cast<as_integer_t<T> >(x)
    @endcode

    @par Notes:

    @c toint cast a floating value to the signed integer value of the same bit size.

    This is done by C casting for scalars and corresponding intrinsic in simd (if available).

    Peculiarly,  that implies that the behaviour of this function on invalid entries is
    not defined and quite unpredictable.

    (For instance it is quite frequent that the test:

    @code
    toint(Inf<double>()) ==  toint(1.0/0.0)
    @endcode

    will return @ref False whilst the test:

    @code
    Inf<double>() == 1.0/0.0
    @endcode

    returns @ref True !)

    If you intend to use @ref Nan and @ref Inf entries,  consider using @ref saturated_(toint) instead
    or its alias @ref ifix.
    Nethertheless, on integral typed values, @c toint acts as identity.

    @see touint

  **/
  IntegerValue toint(Value const & x);
} }
#endif

#include <boost/simd/function/scalar/toint.hpp>
#include <boost/simd/function/simd/toint.hpp>

#endif
