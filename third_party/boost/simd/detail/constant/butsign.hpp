//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_BUTSIGN_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_BUTSIGN_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

  /*
    @ingroup group-constant

    Generate value with all bits set to one except the most significant
    set to zero (the sign bit)

     @return The Butsign constant for the proper type

  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct butsign_ : boost::dispatch::constant_value_<butsign_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,butsign_,boost::dispatch::constant_value_<butsign_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,127> value(boost::dispatch::int8_<X> const&);

        template<typename X>
        static tt::integral_constant<X,32767> value(boost::dispatch::int16_<X> const&);

        template<typename X>
        static tt::integral_constant<X,2147483647> value(boost::dispatch::int32_<X> const&);

        template<typename X>
        static tt::integral_constant<X,9223372036854775807LL> value(boost::dispatch::int64_<X> const&);

        template<typename X>
        static tt::integral_constant<X,127> value(boost::dispatch::uint8_<X> const&);

        template<typename X>
        static tt::integral_constant<X,32767> value(boost::dispatch::uint16_<X> const&);

        template<typename X>
        static tt::integral_constant<X,2147483647> value(boost::dispatch::uint32_<X> const&);

        template<typename X>
        static tt::integral_constant<X,9223372036854775807LL> value(boost::dispatch::uint64_<X> const&);

        template<typename X>
        static nsm::single_<0xEFFFFFFFUL> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static nsm::double_<0xEFFFFFFFFFFFFFFFULL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, butsign_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::butsign_,butsign);
  }

  template<typename T> BOOST_FORCEINLINE auto Butsign()
  BOOST_NOEXCEPT_DECLTYPE(detail::butsign( boost::dispatch::as_<T>{}))
  {
    return detail::butsign( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
