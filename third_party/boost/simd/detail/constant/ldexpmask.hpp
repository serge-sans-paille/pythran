//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_LDEXPMASK_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_LDEXPMASK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the mask to extract the exponent
    bits of a floating point value

    @par Semantic:

    @code
    T r = Ldexpmask<T>();
    @endcode

    @return The Ldexpmask constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;

    struct ldexpmask_ : boost::dispatch::constant_value_<ldexpmask_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,ldexpmask_,boost::dispatch::constant_value_<ldexpmask_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,0x7F800000L> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int64_t,0x7FF0000000000000LL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, ldexpmask_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::ldexpmask_,ldexpmask);
  }

  template<typename T> BOOST_FORCEINLINE auto Ldexpmask()
  BOOST_NOEXCEPT_DECLTYPE(detail::ldexpmask( boost::dispatch::as_<T>{}))
  {
    return detail::ldexpmask( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
