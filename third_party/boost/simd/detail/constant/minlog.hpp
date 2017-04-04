//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MINLOG_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MINLOG_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant Minlog used in logarithm/exponential computations
    boost::simd::log(x) return  0 if x is less than Minlog (underflow)

    @par Semantic:

    @code
    T r = Minlog<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = -708.3964185322641;
    else if T is float
      r = -88.3762626647949
    @endcode

    @see Maxlog


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct minlog_ : boost::dispatch::constant_value_<minlog_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,minlog_,boost::dispatch::constant_value_<minlog_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xc2b0c0a5UL, 0xc086232bdd7abcd2ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, minlog_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::minlog_,minlog);
  }

  template<typename T> BOOST_FORCEINLINE auto Minlog()
  BOOST_NOEXCEPT_DECLTYPE(detail::minlog( boost::dispatch::as_<T>{}))
  {
    return detail::minlog( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
