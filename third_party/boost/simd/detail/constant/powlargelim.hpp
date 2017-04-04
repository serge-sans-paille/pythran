//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_POWLARGELIM_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_POWLARGELIM_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant powlargelim

    @par Semantic:

    @code
    T r = powlargelim<T>();
    @endcode


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct powlargelim_ : boost::dispatch::constant_value_<powlargelim_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,powlargelim_,boost::dispatch::constant_value_<powlargelim_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x44ffe000UL, 0x40cfff8000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, powlargelim_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::powlargelim_,powlargelim);
  }

  template<typename T> BOOST_FORCEINLINE auto Powlargelim()
  BOOST_NOEXCEPT_DECLTYPE(detail::powlargelim( boost::dispatch::as_<T>{}))
  {
    return detail::powlargelim( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
