//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_PIO_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_PIO_2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate t\f$\frac\pi{2}\f$.

    @par Semantic:

    @code
    T r = Pio_2<T>();
    @endcode

    is similar to:

    @code
    T r = T(2*atan(1));
    @endcode

    @return The Pio_2 constant for the proper type
  **/
  template<typename T> T Pio_2();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant pio_2.

      @return The Pio_2 constant for the proper type
    **/
    const boost::dispatch::functor<tag::pio_2_> pio_2 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/pio_2.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
