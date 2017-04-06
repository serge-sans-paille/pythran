//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_PIO2_1T_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_PIO2_1T_HPP_INCLUDED

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
    T r = Pio2_1t<T>();
    @endcode

    @return a value of type T

*/

namespace boost { namespace simd
{
  namespace tag
  {
    struct pio2_1t_ : boost::dispatch::constant_value_<pio2_1t_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pio2_1t_,boost::dispatch::constant_value_<pio2_1t_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X37354443, 0X3DD0B4611A626331LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pio2_1t_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pio2_1t_,pio2_1t);
  }

  template<typename T> BOOST_FORCEINLINE auto Pio2_1t()
  BOOST_NOEXCEPT_DECLTYPE(detail::pio2_1t( boost::dispatch::as_<T>{}))
  {
    return detail::pio2_1t( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
