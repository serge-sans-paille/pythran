//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_DENORMALFACTOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_DENORMALFACTOR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant Denormalfactor used in pedantic rsqrt

    @par Semantic:

    @code
    T r = Denormalfactor<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 2^52;
    else if T is float
      r = 2^24
    @endcode

    @see Maxlog


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct denormalfactor_ : boost::dispatch::constant_value_<denormalfactor_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,denormalfactor_,boost::dispatch::constant_value_<denormalfactor_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x4b800000UL, 0x4330000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, denormalfactor_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::denormalfactor_,denormalfactor);
  }

  template<typename T> BOOST_FORCEINLINE auto Denormalfactor()
  BOOST_NOEXCEPT_DECLTYPE(detail::denormalfactor( boost::dispatch::as_<T>{}))
  {
    return detail::denormalfactor( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
