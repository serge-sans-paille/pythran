//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ELEVEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ELEVEN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the constant eleven.

    @return The Eleven constant for the proper type
  **/
  template<typename T> T Eleven();

  namespace functional
  {
    /*!
      @ingroup group-constant
      Generate the  constant eleven.

      @return The Eleven constant for the proper type
    **/
    Value Eleven();
  }
} }
#endif

#include <boost/simd/constant/definition/eleven.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
