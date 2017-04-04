//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXINIT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXINIT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/constant/definition/valmin.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*

    @ingroup group-constant

    Generate the constant maxinit which is identical to minf for
    arithmetic real types but that must be specialized for complex values ordering.

    maxinit is the value to be returned when a maximum of the elements function is used on an
    empty container.

    @return The Maxinit constant for the proper type
  */

namespace boost { namespace simd
{
  namespace tag
  {
    struct maxinit_ : boost::dispatch::constant_value_<maxinit_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxinit_,boost::dispatch::constant_value_<maxinit_>);

      struct value_map
      {
        template<typename X>
        static auto value(X const& x) -> decltype(valmin_::value_map::value(x));

        template<typename X>
        static nsm::single_<0xFF800000U> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static nsm::double_<0xFFF0000000000000ULL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxinit_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxinit_,maxinit);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxinit()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxinit( boost::dispatch::as_<T>{}))
  {
    return detail::maxinit( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
