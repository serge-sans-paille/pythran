//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MASK2FREXP_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MASK2FREXP_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the constant mask2frexp, a utility mask for frexp implementation.

    @par Semantic:

    @code
    as_integer<T> r = Mask2frexp<T>();
    @endcode

    @code
    if T is double
      r =  4602678819172646912ll;
    else if T is float
      r =  1056964608;
    @endcode

    @return The Mask2frexp constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    namespace tt = nsm::type_traits;

    struct mask2frexp_ : boost::dispatch::constant_value_<mask2frexp_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mask2frexp_,boost::dispatch::constant_value_<mask2frexp_>);

      struct value_map
      {
        template<typename X>
        static tt::integral_constant<X,0> value(boost::dispatch::integer_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int32_t,0x3f000000UL> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static tt::integral_constant<std::int64_t,0x3fe0000000000000ULL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mask2frexp_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mask2frexp_,mask2frexp);
  }

  template<typename T> BOOST_FORCEINLINE auto Mask2frexp()
  BOOST_NOEXCEPT_DECLTYPE(detail::mask2frexp( boost::dispatch::as_<T>{}))
  {
    return detail::mask2frexp( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
