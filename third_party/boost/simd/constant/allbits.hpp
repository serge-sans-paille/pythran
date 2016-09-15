//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ALLBITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generates a value of the chosen type which all bits are set to 1.

    @par Semantic:

    @code
    T r = Allbits<T>();
    @endcode

    is equivalent to:

    - if T is floating point:
      @code
      T r = Nan<T>();
      @endcode

    - otherwise:
      @code
      T r = T(~0);
      @endcode

    @return A value of type @c T with all its bits set to 1

    @see functional::allbits
  **/
  template<typename T> T Allbits();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generates a value of the chosen type which all bits are set to 1.

      @par Semantic:

      For any value @c x of type @c T:
      @code
      T r = simd::functional::allbits( boost::simd::as(x));
      @endcode

      is equivalent to:

      @code
      T r = simd::Allbits<T>();
      @endcode

      @return A value of type @c T with all its bits set to 1

      @see Allbits
    **/
    Value Allbits();
  }
} }
#endif

#include <boost/simd/constant/definition/allbits.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
