//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_RADINDEGR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_RADINDEGR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Constant Radian in Degree residue can help to obtain better conversion
    from Radian to Degree

    @par Semantic:

    For type T:

    @code
    T r = Radindegr<T>();
    @endcode

    @return a value of type T

*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct radindegr_ : boost::dispatch::constant_value_<radindegr_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,radindegr_,boost::dispatch::constant_value_<radindegr_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0XB53387C1, 0XBCE1E7AB456405F8ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, radindegr_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::radindegr_,radindegr);
  }

  template<typename T> BOOST_FORCEINLINE auto Radindegr()
  BOOST_NOEXCEPT_DECLTYPE(detail::radindegr( boost::dispatch::as_<T>{}))
  {
    return detail::radindegr( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
