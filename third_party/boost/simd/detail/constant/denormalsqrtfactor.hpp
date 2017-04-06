//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_DENORMALSQRTFACTOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_DENORMALSQRTFACTOR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Generates constant Denormalsqrtfactor used in pedantic rsqrt

    @par Semantic:

    @code
    T r = Denormalsqrtfactor<T>();
    @endcode

    is similar to:

    @code
    if T is double
      r = 2^26;
    else if T is float
      r = 2^12
    @endcode

    @see Maxlog


*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct denormalsqrtfactor_ : boost::dispatch::constant_value_<denormalsqrtfactor_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,denormalsqrtfactor_,boost::dispatch::constant_value_<denormalsqrtfactor_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x45800000UL, 0x4190000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, denormalsqrtfactor_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::denormalsqrtfactor_,denormalsqrtfactor);
  }

  template<typename T> BOOST_FORCEINLINE auto Denormalsqrtfactor()
  BOOST_NOEXCEPT_DECLTYPE(detail::denormalsqrtfactor( boost::dispatch::as_<T>{}))
  {
    return detail::denormalsqrtfactor( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
