//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_BITINCREMENT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_BITINCREMENT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generates a value of the chosen type which represents the minimal increment value for @c T.

    @par Semantic:

    For any type @c T,

    @code
    T r = Bitincrement<T>();
    @endcode

    generates a value so that, for any value @c x of type @c T,

    @code
    x + r == simd::nextafter(x, 1);
    @endcode

    evaluates to @c true.

    @return A value of type @c T containing the minimal increment value for @c T

    @see functional::bitincrement
  **/
  template<typename T> T Bitincrement();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generates a value of the chosen type which represents the minimal increment value for @c T.

      @par Semantic:

      For any value @c x of type @c T:
      @code
      T r = simd::functional::bitincrement( boost::simd::as(x));
      @endcode

      is similar to:

      @code
      T r = simd::Bitincrement<T>();
      @endcode

      @return A value of type @c T containing the minimal increment value for @c T

      @see Bitincrement
    **/
    Value Bitincrement();
  }
} }
#endif

#include <boost/simd/constant/definition/bitincrement.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
