//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MINLOG2_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MINLOG2_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant Minlog2 used in logarithm/exponential computations
    boost::simd::log2(x) return  0 if x is less than Minlog2 (underflow)

    @par Semantic:

    @code
    T r = Minlog2<T>();
    @endcode

    is similar to:

    @code
    if T is double
    r = -1023.0;
    else if T is float
    r = -127.0;

    @endcode


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct minlog2_ : boost::dispatch::constant_value_<minlog2_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,minlog2_,boost::dispatch::constant_value_<minlog2_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xc2fe0000UL, 0xc08ff00000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, minlog2_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::minlog2_,minlog2);
  }

  template<typename T> BOOST_FORCEINLINE auto Minlog2()
  BOOST_NOEXCEPT_DECLTYPE(detail::minlog2( boost::dispatch::as_<T>{}))
  {
    return detail::minlog2( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
