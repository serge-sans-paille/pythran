//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_CONSTANT_FALSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_CONSTANT_FALSE_HPP_INCLUDED

#include <boost/simd/logical.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( false_, (typename T), bd::cpu_
                          , bd::target_<bd::generic_<bd::unspecified_<T>>>
                          )
  {
    using result = as_logical_t<typename T::type>;

    BOOST_FORCEINLINE result operator()(T const&) const BOOST_NOEXCEPT
    {
      return result(false);
    }
  };
} } }


#endif
