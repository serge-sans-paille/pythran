//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NEGATIVE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NEGATIVE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_negative capabilities

    Returns @ref True if x is negative else @ref False.

    This function differs from @ref is_ltz for floating point arguments,
    because @ref Mzero is negative but not less than zero, and @ref Mzero is
    not positive and not greater than zero, It's probably @ref is_ltz that
    you want.

    @par Semantic:

    @code
    auto r = is_negative(x);
    @endcode

    is similar to:

    @code
    if x is of signed type
      auto r = bitofsign(x) == 1;
    else
      auto r = False;
    @endcode

    @par Note:

    @ref Mzero is the floating point 'minus zero',
    i.e. all bits are @ref Zero but the sign bit.
    Such a value is treated as @ref Zero by IEEE standards.

    behaviour of is_negative on @ref Nan entry is undefined.

    @par Alias

    signbit

    @see is_positive,  Mzero, bitofsign

  **/
  as_logical_t<Value> is_negative(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_negative.hpp>
#include <boost/simd/function/simd/is_negative.hpp>

#endif
