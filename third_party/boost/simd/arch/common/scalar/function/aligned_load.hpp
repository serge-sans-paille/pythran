//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/mask.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/std/iterator.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  //------------------------------------------------------------------------------------------------
  // aligned_load from an input iterator
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer)
                          , bd::cpu_
                          , bd::input_iterator_<bd::scalar_<bd::unspecified_<Pointer>>>
                          , bd::target_< bd::scalar_<bd::unspecified_<Target>> >
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Target const&) const BOOST_NOEXCEPT
    {
      return static_cast<target>(*p);
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_load from a pointer + a misalignment
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Misalignment)
                          , bd::cpu_
                          , bd::pointer_<bd::unspecified_<Pointer>,1u>
                          , bd::constant_< bd::integer_<Misalignment>>
                          , bd::target_< bd::scalar_<bd::unspecified_<Target>> >
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE
    target operator()(Pointer p, Misalignment const&, Target const&) const BOOST_NOEXCEPT
    {
      return static_cast<target>(*(p + Misalignment::value));
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_load from a masked pointer
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bd::cpu_
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>,Zero>
                          , bd::target_< bd::scalar_<bd::unspecified_<Target>> >
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Target const&) const BOOST_NOEXCEPT
    {
      return p.mask() ? boost::simd::aligned_load<target>(p.get()) : static_cast<target>(p.value());
    }
  };
} } }

#endif
