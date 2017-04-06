//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_MAXLOG_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_MAXLOG_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant MaxLog used in logarithm/exponential computations
    log(x) return inf if x is greater than Maxlog (overflow)

    @par Semantic:

    @code
    T r = Maxlog<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 709.78271289338400;
    else if T is float
      r =  88.3762626647949
    @endcode

    @see Minlog


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct maxlog_ : boost::dispatch::constant_value_<maxlog_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,maxlog_,boost::dispatch::constant_value_<maxlog_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x42b0c0a5UL, 0x40862e42fefa39efULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, maxlog_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::maxlog_,maxlog);
  }

  template<typename T> BOOST_FORCEINLINE auto Maxlog()
  BOOST_NOEXCEPT_DECLTYPE(detail::maxlog( boost::dispatch::as_<T>{}))
  {
    return detail::maxlog( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
