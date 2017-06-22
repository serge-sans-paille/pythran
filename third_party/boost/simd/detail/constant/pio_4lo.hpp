//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_PIO_4LO_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_PIO_4LO_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    This constant is such that, for pairs of types (Tup, T)
    (namely (float,  double) and (double, long double)) the sum:

    abs(Tup(Pio_4lo<T>())+Tup(Pio_4<T>())-Pio_4\<Tup\>())  is  less than
    a few Eps<Tup>().

    This is used to improve accuracy when computing sums of the kind
    Pio_4 + x with x small,  by replacing them by Pio_4 + (Pio_4lo+x)

    @par Semantic:

    For type T:

    @code
    T r = Pio_4lo<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 3.061616997868383e-17
    else if T is float
      r = -2.1855694e-08
    @endcode

    @return a value of type T

*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct pio_4lo_ : boost::dispatch::constant_value_<pio_4lo_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pio_4lo_,boost::dispatch::constant_value_<pio_4lo_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0XB2BBBD2EUL, 0X3C81A62633145C07ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pio_4lo_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pio_4lo_,pio_4lo);
  }

  template<typename T> BOOST_FORCEINLINE auto Pio_4lo()
  BOOST_NOEXCEPT_DECLTYPE(detail::pio_4lo( boost::dispatch::as_<T>{}))
  {
    return detail::pio_4lo( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
