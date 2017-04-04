//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXLOG10_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXLOG10_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant MaxLog10 used in logarithm/exponential computations
    log10(x) return inf if x is greater than Maxlog10 (overflow)

    @par Semantic:

    @code
    T r = Maxlog10<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 308.2547155599167;
    else if T is float
      r = 38.23080825805664;

    @endcode


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct maxlog10_ : boost::dispatch::constant_value_<maxlog10_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxlog10_,boost::dispatch::constant_value_<maxlog10_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x4218ec59UL, 0x40734413509f79feULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxlog10_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxlog10_,maxlog10);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxlog10()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxlog10( boost::dispatch::as_<T>{}))
  {
    return detail::maxlog10( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
