//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing bits capabilities

    Returns an unsigned integer value which has the same bits as the input

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = bits(x);
    @endcode

    is equivalent to:

    @code
    as_integer_t<T,unsigned> r = bitwise_cast< as_integer_t<T,unsigned>>(x);
    @endcode

  **/
  as_integer_t<T, unsigned> bits(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/bits.hpp>
#include <boost/simd/function/simd/bits.hpp>

#endif
