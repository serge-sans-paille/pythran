//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_CGOLD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CGOLD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant
    Generates a value of the chosen type which represents the conjugate Golden Ratio.

    The conjugate Golden Ratio (\f$\bar\phi\f$) is defined as \f$\frac{1-\sqrt5}{2}\f$.

    @par Semantic:

    @code
    T r = Cgold<T>();
    @endcode

    is equivalent to:

    @code
    T r = (1-simd::sqrt(T(5)))/2;
    @endcode

    @return A value of type @c T containing the conjugate Golden Ratio.

    @see functional::cgold
  **/
  template<typename T> T Cgold();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generates a value of the chosen type which represents the conjugate Golden Ratio.

      The conjugate Golden Ratio (\f$\bar\phi\f$) is defined as \f$\frac{1-\sqrt5}{2}\f$.

      @par Semantic:

      For any value @c x of type @c T:
      @code
      T r = simd::functional::cgold( boost::simd::as(x));
      @endcode

      is equivalent to:

      @code
      T r = simd::Cgold<T>();
      @endcode

      @return A value of type @c T containing the conjugate Golden Ratio.

      @see Cgold
    **/
    Value Cgold();
  }
} }
#endif

#include <boost/simd/constant/definition/cgold.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
