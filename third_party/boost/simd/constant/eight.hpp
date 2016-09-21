//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_EIGHT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_EIGHT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generates a value of the chosen type equals to eight.

    @par Semantic:

    @code
    T r = Eight<T>();
    @endcode

    is equivalent to:

    @code
    T r = static_cast<T>(8);
    @endcode

    @return A value of type @c T equals to eight.

    @see functional::eight
  **/
  template<typename T> T Eight();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generates a value of the chosen type equals to eight.

      @par Semantic:

      For any value @c x of type @c T:
      @code
      T r = simd::functional::eight( boost::simd::as(x));
      @endcode

      is equivalent to:

      @code
      T r = simd::Eight<T>();
      @endcode

      @return A value of type @c T containing the value eight.

      @see Eight
    **/
    Value Eight();
  }
} }
#endif

#include <boost/simd/constant/definition/eight.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
