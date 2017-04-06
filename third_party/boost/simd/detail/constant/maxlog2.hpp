//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXLOG2_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXLOG2_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant MaxLog2 used in logarithm/exponential computations
    log2(x) return inf if x is greater than Maxlog2 (overflow)

    @par Semantic:

    @code
    T r = Maxlog2<T>();
    @endcode

    is similar to:

    @code
    if T is double
    r = 1023.0;
    else if T is float
    r = 127.0;

    @endcode


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct maxlog2_ : boost::dispatch::constant_value_<maxlog2_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxlog2_,boost::dispatch::constant_value_<maxlog2_>);
      BOOST_SIMD_REGISTER_CONSTANT( 0, 0x42fe0000UL, 0x408ff80000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxlog2_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxlog2_,maxlog2);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxlog2()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxlog2( boost::dispatch::as_<T>{}))
  {
    return detail::maxlog2( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
