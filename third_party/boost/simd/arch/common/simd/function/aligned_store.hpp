//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // Whenever we store with an offset
  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Src, typename Pointer, typename X, typename A2)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          , bd::scalar_<bd::integer_<A2>>
                          )
  {
    BOOST_FORCEINLINE void operator()(Src const& a0, Pointer a1, A2 const & a2) const BOOST_NOEXCEPT
    {
      bs::aligned_store(a0,a1+a2);
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_store is generally check + calling store
  BOOST_DISPATCH_OVERLOAD( aligned_store_
                          , (typename Src, typename Pointer, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>,X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer p) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p,Src::alignment)
                      , "boost::simd::aligned_store was performed on an unaligned pointer of integer"
                      );

      do_(s, p, typename Src::storage_kind{}, typename Src::traits::element_range{} );
    }

    // aggregate pack are calling store twice
    template<typename... N> static BOOST_FORCEINLINE
    void do_( Src const & s, Pointer p, aggregate_storage const&, nsm::list<N...> const&)
    {
      aligned_store(slice_low(s) , p);
      aligned_store(slice_high(s), p+Src::traits::element_size);
    }

    // other pack are calling store N times
    template<typename I> static BOOST_FORCEINLINE void sto_(const Src& s, Pointer  p)
    {
      using s_t = typename boost::pointee<Pointer>::type;
      p[I::value] = static_cast<s_t>(extract<I::value>(s));
    }

    template<typename K, typename... N>
    static BOOST_FORCEINLINE void do_(Src const & s, Pointer p, K const&, nsm::list<N...> const&)
    {
      (void)(std::initializer_list<bool>{(sto_<N>(s,p),true)...});
    }
  };

  //------------------------------------------------------------------------------------------------
  // aligned_store data to a masked pointer = check + call store
  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Src, typename Pointer, typename Zero, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>,Zero>
                          )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer const& p) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p.get(),Src::alignment)
                      , "boost::simd::aligned_store was performed on an unaligned pointer"
                      );

      store(s,p);
    }
  };

  //------------------------------------------------------------------------------------------------
  // store data to a masked pointer from whatever in a pack
  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Src, typename Pointer, typename Zero, typename X, typename A2)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::masked_pointer_<bd::scalar_<bd::unspecified_<Pointer>>,Zero>
                          , bd::scalar_<bd::integer_<A2>>
                          )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer const& p, A2 idx) const
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(p.get()+idx,Src::alignment)
                      , "boost::simd::aligned_store was performed on an unaligned pointer"
                      );

      store(s,p,idx);
    }
  };
} } }

#endif
