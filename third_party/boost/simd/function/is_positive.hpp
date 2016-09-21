//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_POSITIVE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_POSITIVE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_positive capabilities

    Returns @ref True if x is positive else @ref False.

    This function differs from @ref is_gtz for floating point arguments,
    because @ref Zero is positive but not greater than 0, and @ref Mzero is
    not positive and not greater than 0, It's probably @ref is_gtz that
    you want.

    @par Semantic:

    @code
    auto r = is_positive(x);
    @endcode

    is similar to:

    @code
    if x is of signed type
      auto r = bitofsign(x) == 0;
    else
      auto r = True ;
    @endcode

    @par Note:

    Mzero is the floating point 'minus zero',
    i.e. all bits are @ref Zero but the sign bit.
    Such a value is treated as @ref Zero by ieee standards.

    behaviour of is_positive on @ref Nan is undefined.

    @see is_negative,  Mzero, bitofsign

  **/
  as_logical_t<Value> is_positive(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_positive.hpp>
#include <boost/simd/function/simd/is_positive.hpp>

#endif
