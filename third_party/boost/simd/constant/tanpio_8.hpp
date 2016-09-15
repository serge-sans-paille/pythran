//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TANPIO_8_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TANPIO_8_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant \f$\tan3\frac\pi{8} = \sqrt2 - 1\f$.

    @par Semantic:

    For type T:

    @code
    T r = Tanpio_8<T>();
    @endcode

    is similar to:

    @code
    T r = sqrt(2.0)-1.0;
    @endcode

    @return a value of type T

**/
  template<typename T> T Tanpio_8();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant \f$\tan3\frac\pi{8} = \sqrt2 - 1\f$.

      Generate the  constant tanpio_8.

      @return The Tanpio_8 constant for the proper type
    **/
    const boost::dispatch::functor<tag::tanpio_8_> tanpio_8 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/tanpio_8.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
