//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MEANOF_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MEANOF_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing meanof capabilities

    Computes the mean of its parameter avoiding overflow.

    @par semantic:
    For any given value @c x and @c y of type @c T:

    @code
    T r = meanof(x, y);
    @endcode

    is similar to:

    @code
    T r = (x+y)/2;
    @endcode

    @par Note:
    Take care that for integers the value returned can differ by one unit
    from \c ceil((a+b)/2.0) or \c floor((a+b)/2.0), but is always one of
    the two values.

    @see average

  **/
  Value meanof(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/meanof.hpp>
#include <boost/simd/function/simd/meanof.hpp>

#endif
