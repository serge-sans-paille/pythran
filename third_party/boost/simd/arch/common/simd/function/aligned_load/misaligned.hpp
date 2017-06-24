//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_LOAD_MISALIGNED_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_LOAD_MISALIGNED_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/assert.hpp>

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4308) // signed/unsigned conversion
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;
  //------------------------------------------------------------------------------------------------
  // aligned_load from a pointer of whatever + Misalignment
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Misalignment, typename Ext)
                          , bd::cpu_
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          , bd::constant_< bd::integer_<Misalignment>>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,Ext>>
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    BOOST_FORCEINLINE target_t operator()(Pointer p, Misalignment const& m, Target const&) const
    {
      static const std::size_t                        card = target_t::static_size;
      static const typename Misalignment::value_type  unalignment = Misalignment::value % card;

      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p-Misalignment::value,target_t::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer"
                      );

      return do_( p, m, nsm::bool_<unalignment != 0>()
                , typename target_t::storage_kind(), typename target_t::traits::static_range{}
                );
    }

    // Aggregate case: fill in the storage by calling load twice
    template<typename... N> static BOOST_FORCEINLINE
    target_t do_( Pointer p, Misalignment const&, tt::true_type const&
                , aggregate_storage const&, nsm::list<N...> const&
                ) BOOST_NOEXCEPT
    {
      using sv_t = typename storage_t::value_type;
      return combine( aligned_load<sv_t,Misalignment::value>(p)
                    , aligned_load<sv_t,Misalignment::value>(p+target_t::traits::element_size)
                    );
    }

    template<typename... N> static BOOST_FORCEINLINE
    target_t do_( Pointer p, Misalignment const&, tt::false_type const&
                , aggregate_storage const&, nsm::list<N...> const&
                ) BOOST_NOEXCEPT
    {
      using sv_t = typename storage_t::value_type;
      return combine( aligned_load<sv_t>(p)
                    , aligned_load<sv_t>(p+target_t::traits::element_size)
                    );
    }

    // Other case: Fill a pack piecewise
    template<typename K, typename... N> static BOOST_FORCEINLINE
    target_t do_( Pointer p, Misalignment const&, tt::true_type const&
                , K const&, nsm::list<N...> const&
                ) BOOST_NOEXCEPT
    {
      return target_t(static_cast<typename target_t::value_type>(p[N::value])...);
    }

    template<typename K, typename... N> static BOOST_FORCEINLINE
    target_t do_( Pointer p, Misalignment const&, tt::false_type const&
                , K const&, nsm::list<N...> const&
                ) BOOST_NOEXCEPT
    {
      return aligned_load<target_t>(p);
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_load from a pointer of logical to whatever with misalignment
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Misalignment, typename Ext)
                          , bd::cpu_
                          , bd::pointer_<bd::scalar_<bs::logical_<Pointer>>,1u>
                          , bd::constant_< bd::integer_<Misalignment>>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,Ext>>
                          )
  {
    using target_t  = typename Target::type;

    BOOST_FORCEINLINE target_t operator()(Pointer p, Misalignment const&, Target const&) const
    {
      return load<target_t>(p+Misalignment::value);
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_load from a pointer of arithmetic to a pack of logical with misalignment
  BOOST_DISPATCH_OVERLOAD ( aligned_load_
                          , (typename Target, typename Pointer, typename Misalignment, typename Ext)
                          , bd::cpu_
                          , bd::pointer_<bd::scalar_<bd::arithmetic_<Pointer>>,1u>
                          , bd::constant_< bd::integer_<Misalignment>>
                          , bd::target_<bs::pack_<bs::logical_<Target>,Ext>>
                          )
  {
    using target_t  = typename Target::type;

    BOOST_FORCEINLINE target_t operator()(Pointer p, Misalignment const&, Target const&) const
    {
      return aligned_load<bs::as_arithmetic_t<target_t>,Misalignment::value>(p) != 0;
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
