//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_PIO_2LO_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_PIO_2LO_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    This constant is such that, for pairs of types (T, Tup)
    (namely (float,  double) and (double, long double)) the sum:

    abs(Tup(Pio_2lo<T>())+Tup(Pio_2<T>())-Pio_2\< Tup \>()) is  less than
    a few Eps<Tup>().


    This is used to improve accuracy when computing sums of the kind
    \f$\pi/2 + x\f$ with x small,  by replacing them by
    Pio_2 + (Pio_2lo + x)

    @par Semantic:

    For type T:

    @code
    T r = Pio_2lo<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 6.123233995736766e-17
    else if T is float
      r = -4.3711388e-08
    @endcode

    @return a value of type T

*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct pio_2lo_ : boost::dispatch::constant_value_<pio_2lo_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pio_2lo_,boost::dispatch::constant_value_<pio_2lo_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0XB33BBD2EUL, 0X3C91A62633145C07ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pio_2lo_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pio_2lo_,pio_2lo);
  }

  template<typename T> BOOST_FORCEINLINE auto Pio_2lo()
  BOOST_NOEXCEPT_DECLTYPE(detail::pio_2lo( boost::dispatch::as_<T>{}))
  {
    return detail::pio_2lo( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
