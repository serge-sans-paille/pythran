//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_LOG10_2LO_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_LOG10_2LO_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant log10_2lo.This constant is coupled with Log10_2hi and is
    used in the float logarithms computations
    We have abs( double(log10_2lo<float>())+double(Log10_2hi<float>()) - Log10(2.0))) < 3e-11

    @par Semantic:

    @code
    T r = log10_2lo<T>();
    @endcode


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct log10_2lo_ : boost::dispatch::constant_value_<log10_2lo_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,log10_2lo_,boost::dispatch::constant_value_<log10_2lo_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x39826a14UL, 0x3ed3509f79fef312ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, log10_2lo_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::log10_2lo_,log10_2lo);
  }

  template<typename T> BOOST_FORCEINLINE auto Log10_2lo()
  BOOST_NOEXCEPT_DECLTYPE(detail::log10_2lo( boost::dispatch::as_<T>{}))
  {
    return detail::log10_2lo( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
