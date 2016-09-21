//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_HALF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_HALF_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value \f$\frac12\f$

    @par Semantic:

    @code
    T r = Half<T>();
    @endcode

    is similar for floating types to:

    @code
    T r = T(1)/T(2);
    @endcode

    (0 for integral types)

    @return The Half constant for the proper type
  **/
  template<typename T> T Half();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant half.

      @return The Half constant for the proper type
    **/
    Value Half();
  }
} }
#endif

#include <boost/simd/constant/definition/half.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
