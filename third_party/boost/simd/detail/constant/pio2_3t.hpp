//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_PIO2_3T_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_PIO2_3T_HPP_INCLUDED

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
    T r = Pio2_3t<T>();
    @endcode

    @return a value of type T

*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct pio2_3t_ : boost::dispatch::constant_value_<pio2_3t_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pio2_3t_,boost::dispatch::constant_value_<pio2_3t_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X248D3132, 0X397B839A252049C1LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pio2_3t_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pio2_3t_,pio2_3t);
  }

  template<typename T> BOOST_FORCEINLINE auto Pio2_3t()
  BOOST_NOEXCEPT_DECLTYPE(detail::pio2_3t( boost::dispatch::as_<T>{}))
  {
    return detail::pio2_3t( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
