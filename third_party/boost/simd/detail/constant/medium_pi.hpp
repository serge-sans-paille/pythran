//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MEDIUM_PI_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MEDIUM_PI_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Constant used in trigonometric reductions

    @par Semantic:

    For type T:

    @code
    T r = Medium_pi<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = Pi<T>()*pow2(18);
    else if T is float
      r = Pi<T>()*pow2(6);
    else
      r =  201
    @endcode

    @return a value of type T

*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct medium_pi_ : boost::dispatch::constant_value_<medium_pi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,medium_pi_,boost::dispatch::constant_value_<medium_pi_>);
      BOOST_SIMD_REGISTER_CONSTANT(201, 0X43490FDB, 0X412921FB54442D18LL); //2^6/pi, //2^{18}/pi;
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, medium_pi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::medium_pi_,medium_pi);
  }

  template<typename T> BOOST_FORCEINLINE auto Medium_pi()
  BOOST_NOEXCEPT_DECLTYPE(detail::medium_pi( boost::dispatch::as_<T>{}))
  {
    return detail::medium_pi( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
