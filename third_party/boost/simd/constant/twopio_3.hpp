//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOPIO_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOPIO_3_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant \f$2\frac\pi{3}\f$.

    @par Semantic:

    For type T:

    @code
    T r = Twopio_3<T>();
    @endcode

    is similar to:

    @code
    T r = Two<T>()*Pi<T>()/Three<T>();
    @endcode

    @return a value of type T

**/
  template<typename T> T Twopio_3();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant \f$2\frac\pi{3}\f$.

      Generate the  constant twopio_3.

      @return The Twopio_3 constant for the proper type
    **/
    const boost::dispatch::functor<tag::twopio_3_> twopio_3 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/twopio_3.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
