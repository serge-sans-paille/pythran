//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOAD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOAD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/mask.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/dispatch/adapted/std/iterator.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  //------------------------------------------------------------------------------------------------
  // load from an input iterator
  BOOST_DISPATCH_OVERLOAD ( load_
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
  // load from an input range
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Begin, typename End)
                          , bd::cpu_
                          , bd::input_iterator_<bd::scalar_<bd::unspecified_<Begin>>>
                          , bd::input_iterator_<bd::scalar_<bd::unspecified_<End>>>
                          , bd::target_< bd::scalar_<bd::unspecified_<Target>> >
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Begin b, End, Target const&) const BOOST_NOEXCEPT
    {
      return *b;
    }
  };

  //------------------------------------------------------------------------------------------------
  // load from a masked pointer
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero)
                          , bd::cpu_
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>, Zero>
                          , bd::target_< bd::scalar_<bd::unspecified_<Target>> >
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Target const&) const BOOST_NOEXCEPT
    {
      return p.mask() ? boost::simd::load<target>(p.get()) : static_cast<target>(p.value());
    }
  };

  //------------------------------------------------------------------------------------------------
  // load from a masked pointer and an integral offset
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Zero, typename Offset)
                          , bd::cpu_
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>,Zero>
                          , bd::scalar_<bd::integer_<Offset>>
                          , bd::target_< bd::scalar_<bd::unspecified_<Target>> >
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Pointer p, Offset o, Target const&) const BOOST_NOEXCEPT
    {
      return p.mask() ? boost::simd::load<target>(p.get(),o) : static_cast<target>(p.value());
    }
  };
} } }

#endif
