//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SWAPBYTES_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing swapbytes capabilities

    Reverse the byte order of each scalar value

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = swapbytes(x);
    @endcode

  **/
  Value swapbytes(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/swapbytes.hpp>
#include <boost/simd/function/simd/swapbytes.hpp>

#endif
