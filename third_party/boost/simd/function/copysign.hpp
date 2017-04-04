//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COPYSIGN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COPYSIGN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns @c x with the sign of @c y.

    @par Header <boost/simd/function/copysign.hpp>

    @see sign, signnz, is_positive


    @par Example:

      @snippet copysign.cpp copysign

    @par Possible output:

      @snippet copysign.txt copysign

  **/
  Value copysign(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/copysign.hpp>
#include <boost/simd/function/simd/copysign.hpp>

#endif
