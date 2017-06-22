//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_ALL_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_ALL_REDUCE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/shuffle.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace tt = nsm::type_traits;

  //------------------------------------------------------------------------------------------------
  // This meta-permutation implements the butterfly pattern required for log-tree based reductions.
  //
  // V is a vector of cardinal 4 :          [ v0 | v1 | v2 | v3 ]
  // The log-tree reduction will require :  [ v2 | v3 | v0 | v1 ]
  // and :                                  [ v3 | v2 | v1 | v0 ]
  //
  // Basically this requires permuting cardinal/2^n value at each iteration
  // stopping when only 1 element is left to be permuted.
  //------------------------------------------------------------------------------------------------
  template<int Step> struct butterfly_perm
  {
    template<typename I, typename>
    struct  apply : tt::integral_constant<int,(I::value >= Step) ? I::value-Step : I::value+Step>
    {};
  };

  template<int Step> struct butterfly
  {
    using next_t = butterfly<Step/2>;
    template<typename Op, typename V>
    BOOST_FORCEINLINE
    auto  operator()(Op const& op, V const& a0) const BOOST_NOEXCEPT
          -> decltype( next_t{}( op, op(a0, boost::simd::shuffle< butterfly_perm<Step> >(a0)) ) )
    {
      next_t next;
      return next( op, op(a0, boost::simd::shuffle< butterfly_perm<Step> >(a0)) );
    }
  };

  template<> struct butterfly<1>
  {
    template<typename Op, typename V>
    BOOST_FORCEINLINE
    auto  operator()(Op const& op, V const& a0) const BOOST_NOEXCEPT
          ->  decltype( op(boost::simd::shuffle< butterfly_perm<1> >(a0),a0) )
    {
      return op(boost::simd::shuffle< butterfly_perm<1> >(a0),a0);
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_FALLBACK  ( ( typename BinOp, typename Neutral
                                      , typename Arg, typename Ext
                                      )
                                    , tag::all_reduce_
                                    , bd::cpu_
                                    , bd::elementwise_<BinOp>
                                    , bs::pack_<bd::unspecified_<Neutral>, Ext>
                                    , bs::pack_<bd::unspecified_<Arg>, Ext>
                                    )
  {
    using function_t  = bd::functor<BinOp>;
    using result_t    = decltype( bd::functor<BinOp>()( bd::detail::declval<Arg>()
                                                      , bd::detail::declval<Neutral>()
                                                      )
                                );

    // ---------------------------------------------------------------------------------------------
    // singleton case
    template<typename K, typename N> static BOOST_FORCEINLINE
    result_t fold_( function_t const& op, Neutral const& z, Arg const& a0
                  , K const&, nsm::list<N> const&
                  )
    {
      return op( z, a0 );
    }

    // ---------------------------------------------------------------------------------------------
    // Native case
    template<typename N0, typename N1, typename... N> static BOOST_FORCEINLINE
    result_t fold_( function_t const& op, Neutral const& z, Arg const& a0
                  , native_storage const&, nsm::list<N0,N1,N...> const&
                  )
    {
      return op(detail::butterfly<Arg::static_size/2>{}(op,a0),z);
    }

    // ---------------------------------------------------------------------------------------------
    // Aggregate case
    template<typename N0, typename N1, typename... N> static BOOST_FORCEINLINE
    result_t fold_( function_t const& op, Neutral const& z, Arg const& a0
                  , aggregate_storage const&, nsm::list<N0,N1,N...> const&
                  )
    {
      auto  r = detail::all_reduce(op,z.storage()[0],a0.storage()[0]);
            r = detail::all_reduce(op,r,a0.storage()[1]);
      return combine(r,r);
    }

    // ---------------------------------------------------------------------------------------------
    // Scalar case
    template<typename N0, typename N1, typename... N> static BOOST_FORCEINLINE
    result_t fold_( function_t const& op, Neutral const& z, Arg const& a0
                  , scalar_storage const&, nsm::list<N0,N1,N...> const&
                  )
    {
      auto r = op( bs::extract<0>(a0), z );
           r = op( bs::extract<1>(a0), r );

      (void)std::initializer_list<bool> { ((r = op(bs::extract<N::value>(a0),r)),true)... };

      return result_t(r);
    }

    BOOST_FORCEINLINE result_t
    operator()(function_t const& op, Neutral const& z, Arg const& a0) const
    {
      return fold_(op, z, a0, typename Arg::storage_kind{}, typename Arg::traits::static_range{});
    }
  };
} } }

#endif
