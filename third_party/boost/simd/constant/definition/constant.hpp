//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_CONSTANT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_CONSTANT_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <cstdint>

namespace boost { namespace simd
{
  namespace tag
  {
    struct constant_ : boost::dispatch::constant_value_<constant_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,constant_,boost::dispatch::constant_value_<constant_>);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, constant_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::constant_,constant);
  }

  template<typename Type, detail::bits_t<dispatch::scalar_of_t<Type>> Bits>
  BOOST_FORCEINLINE Type Constant()
  {
    using cst_t = typename detail::constantify<boost::dispatch::scalar_of_t<Type>,Bits>::type;
    return detail::constant( cst_t{}, boost::simd::as_<Type>{} );
  }
} }

#endif
