//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITOFSIGN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITOFSIGN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns a value of the same type as
    the input with all bits set to zero
    except the sign bit which is preserved.
    This function object returns always @ref Zero for unsigned types


    @par Header <boost/simd/function/bitofsign.hpp>

    @par Example:

      @snippet bitofsign.cpp bitofsign

    @par Possible output:

      @snippet bitofsign.txt bitofsign

  **/
  Value bitofsign(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/bitofsign.hpp>
#include <boost/simd/function/simd/bitofsign.hpp>

#endif
