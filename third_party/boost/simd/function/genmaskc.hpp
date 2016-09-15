//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_GENMASKC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_GENMASKC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing genmaskc capabilities

    Returns a mask of bits. All ones if the
    input element is @ref Zero else all zeros.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = genmaskc(x);
    @endcode

    is similar to

    @code
    T r = x ? Zero : Allbits;
    @endcode

    @par Alias:
    @c if_zero_else_allbits

    @see if_else_allbits

  **/
  Value genmaskc(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/genmaskc.hpp>
#include <boost/simd/function/simd/genmaskc.hpp>

#endif
