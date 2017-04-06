//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_POWLOWLIM_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_POWLOWLIM_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant powlowlim

    @par Semantic:

    @code
    T r = powlowlim<T>();
    @endcode


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct powlowlim_ : boost::dispatch::constant_value_<powlowlim_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,powlowlim_,boost::dispatch::constant_value_<powlowlim_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xc5160000UL, 0xc0d0c7c000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, powlowlim_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::powlowlim_,powlowlim);
  }

  template<typename T> BOOST_FORCEINLINE auto Powlowlim()
  BOOST_NOEXCEPT_DECLTYPE(detail::powlowlim( boost::dispatch::as_<T>{}))
  {
    return detail::powlowlim( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
