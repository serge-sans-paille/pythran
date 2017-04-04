//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MTWO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MTWO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the constant mtwo.

    @return The Mtwo constant for the proper type
  **/
  template<typename T> T Mtwo();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant mtwo.

      @return The Mtwo constant for the proper type
    **/
    Value Mtwo();
  }
} }
#endif

#include <boost/simd/constant/scalar/mtwo.hpp>
#include <boost/simd/constant/simd/mtwo.hpp>

#endif
