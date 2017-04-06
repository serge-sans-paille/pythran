//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_PIX2_1_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_PIX2_1_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

/*


    @ingroup group-constant

    Constant used in modular computation involving \f$\pi\f$

    @par Semantic:

    For type T:

    @code
    T r = Pix2_1<T>();
    @endcode

    @return a value of type T

*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct pix2_1_ : boost::dispatch::constant_value_<pix2_1_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pix2_1_,boost::dispatch::constant_value_<pix2_1_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0X40C90F00, 0X401921FB54400000LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pix2_1_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pix2_1_,pix2_1);
  }

  template<typename T> BOOST_FORCEINLINE auto Pix2_1()
  BOOST_NOEXCEPT_DECLTYPE(detail::pix2_1( boost::dispatch::as_<T>{}))
  {
    return detail::pix2_1( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
