//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/mask.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  //------------------------------------------------------------------------------------------------
  // aligned_load from an pointer and an integral offset
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Offset)
                          , bd::cpu_
                          , bd::pointer_<bd::unspecified_<Pointer>,1u>
                          , bd::scalar_<bd::integer_<Offset>>
                          , bd::target_<bd::unspecified_<Target>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Offset o, Target const&) const BOOST_NOEXCEPT
    {
      return boost::simd::aligned_load<target>(p+o);
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_load from an pointer, a misalignment and an integral offset
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , ( typename Target, typename Pointer
                            , typename Offset, typename Misalignment
                            )
                          , bd::cpu_
                          , bd::pointer_<bd::unspecified_<Pointer>,1u>
                          , bd::scalar_<bd::integer_<Offset>>
                          , bd::constant_< bd::integer_<Misalignment>>
                          , bd::target_<bd::unspecified_<Target>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE
    target operator()(Pointer p, Offset o, Misalignment const&, Target const&) const BOOST_NOEXCEPT
    {
      return boost::simd::aligned_load<target,Misalignment::value>(p+o);
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_load from a masked pointer and an integral offset
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Offset)
                          , bd::cpu_
                          , bd::masked_pointer_<bd::unspecified_<Pointer>,tt::false_type>
                          , bd::scalar_<bd::integer_<Offset>>
                          , bd::target_<bd::unspecified_<Target>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Offset o, Target const&) const BOOST_NOEXCEPT
    {
      return boost::simd::aligned_load<target>(boost::simd::mask(p.get()+o,p.value(),p.mask()));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Offset)
                          , bd::cpu_
                          , bd::masked_pointer_<bd::unspecified_<Pointer>,tt::true_type>
                          , bd::scalar_<bd::integer_<Offset>>
                          , bd::target_<bd::unspecified_<Target>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Offset o, Target const&) const BOOST_NOEXCEPT
    {
      return boost::simd::aligned_load<target>(boost::simd::mask(p.get()+o,p.mask()));
    }
  };
} } }

#endif
