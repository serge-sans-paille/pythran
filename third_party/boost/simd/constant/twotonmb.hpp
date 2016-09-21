//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOTONMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOTONMB_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate two to the number of mantissa bits.

    @par Semantic:

    @code
    T r = Twotonmb<T>();
    @endcode

    is similar to:

    @code
    T r = pow(2, Nbmantissabits<T>());
    @endcode

    @return The Twotonmb constant for the proper type
  **/
  template<typename T> T Twotonmb();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant twotonmb.

      @return The Twotonmb constant for the proper type
    **/
    Value Twotonmb();
  }
} }
#endif

#include <boost/simd/constant/definition/twotonmb.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
