//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_LOG10_EHI_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_LOG10_EHI_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant log10_ehi.This constant is coupled with Log10_elo and is
    used in the float logarithms computations
    We have double(log10_ehi<float>())+double(Log10_elo<float>()) == Log_10(e)

    @par Semantic:

    @code
    T r = log10_ehi<T>();
    @endcode


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct log10_ehi_ : boost::dispatch::constant_value_<log10_ehi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,log10_ehi_,boost::dispatch::constant_value_<log10_ehi_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3ede0000UL, 0x3fdbcb7b1526e510ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, log10_ehi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::log10_ehi_,log10_ehi);
  }

  template<typename T> BOOST_FORCEINLINE auto Log10_ehi()
  BOOST_NOEXCEPT_DECLTYPE(detail::log10_ehi( boost::dispatch::as_<T>{}))
  {
    return detail::log10_ehi( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
