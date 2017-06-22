//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_AUTOSCAN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_AUTOSCAN_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/shuffle.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  //------------------------------------------------------------------------------------------------
  // This meta-permutation implements the scan pattern required for scan-trees.
  template<int Step> struct scan_perm
  {
    template<typename I, typename> struct apply
    {
      static const int relative_index = I::value / Step;
      static const int index = relative_index % 2 ? (relative_index*Step - 1) : -1;
      using type = tt::integral_constant<int,index>;
    };
  };
  //------------------------------------------------------------------------------------------------
  // This meta-function implements the scan pattern mask to handle scan-tree neutral element
  template<int Step> struct scan_mask
  {
    template<typename T, int I> struct apply
    {
      static const int relative_index = I / Step;
      using type = tt::integral_constant<T,relative_index % 2 ? T(0) : T(~0)>;
    };

    template<typename V, typename... N>
    static BOOST_FORCEINLINE V mask(V const& z, nsm::list<N...> const&)
    {
      using pi_t = boost::dispatch::as_integer_t<V>;
      return z & pi_t( apply<typename pi_t::value_type, N::value>::type::value... );
    }
    template<typename V> static BOOST_FORCEINLINE V mask(V const& z)
    {
      return mask(z, typename V::traits::element_range{});
    }
  };

  template<int Step, int Cardinal> struct scan
  {
    using next_t = scan<Step*2,Cardinal>;
    template<typename Op, typename V, typename U>
    BOOST_FORCEINLINE U operator()(Op const& op, V const& a0, U const& z) const BOOST_NOEXCEPT
    {
      // we perform a unary shuffle + mask in order to ensure that most ISA can
      // generate the scan-tree pattern without using an emulated shuffle
      // TODO: Make this dependent on has_native_shuffle<ABI>
      auto shf = boost::simd::shuffle< scan_perm<Step> >(a0) | scan_mask<Step>::mask(z);
      next_t next;
      return next( op, op(a0, shf), z );
    }
  };

  template<int End> struct scan<End,End>
  {
    template<typename Op, typename V, typename U>
    BOOST_FORCEINLINE U  operator()(Op const& op, V const& a0, U const& z) const BOOST_NOEXCEPT
    {
      auto shf = boost::simd::shuffle< scan_perm<End> >(a0) | scan_mask<End>::mask(z);
      return op(a0, shf);
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_FALLBACK( ( typename F, typename BinOp, typename NeutralElement
                                    , typename Arg, typename Ext
                                    )
                                  , bd::cumulative_<F,BinOp,NeutralElement>
                                  , bd::cpu_
                                  , bs::pack_<bd::unspecified_<Arg>, Ext>
                                  )
  {
    using scalar_t  = decltype( bd::functor<F>()( bd::detail::declval<typename Arg::value_type>() ) );
    using result_t  = typename Arg::template rebind<scalar_t>;
    using function_t = bd::functor<BinOp>;

    // ---------------------------------------------------------------------------------------------
    // Aggregate case
    template<typename... N> static BOOST_FORCEINLINE
    result_t do_( function_t const& op, result_t const&, Arg const& a0
                , aggregate_storage const&, nsm::list<N...> const&
                )
    {
      bd::functor<F>      f;

      auto lo = f(a0.storage()[0]);
      return combine( lo, op( lo.back(), f(a0.storage()[1])) );
    }

    // ---------------------------------------------------------------------------------------------
    // singleton case
    template<typename K, typename N> static BOOST_FORCEINLINE
    result_t do_( function_t const&, result_t const&
                , Arg const& a0, K const&, nsm::list<N> const&
                )
    {
      return a0;
    }

    // ---------------------------------------------------------------------------------------------
    // Native case
    template<typename N0, typename N1, typename... N> static BOOST_FORCEINLINE
    result_t do_( function_t const& op, result_t const& z, Arg const& a0
                , native_storage const&, nsm::list<N0,N1,N...> const&
                )
    {
      return detail::scan<1,Arg::static_size/2>{}(op,a0,z);
    }

    // ---------------------------------------------------------------------------------------------
    // Scalar case
    template<typename N0, typename N1, typename... N> static BOOST_FORCEINLINE
    result_t do_( function_t const& op, result_t const&, Arg const& a0
                , scalar_storage const&, nsm::list<N0,N1,N...> const&
                )
    {
      result_t that = a0;
      that[1] = op(bs::extract<1>(a0), bs::extract<0>(that));

      (void)std::initializer_list<bool> { ( ( that[N::value] = op ( bs::extract<N::value>(a0)
                                                                  , bs::extract<N::value-1>(that)
                                                                  )
                                            ),true
                                          )...
                                        };

      return that;
    }

    BOOST_FORCEINLINE result_t operator()(Arg const& a0) const
    {
      return do_( function_t{}
                , bd::functor<NeutralElement>{}(as_<result_t>{})
                , a0, typename Arg::storage_kind{}, typename Arg::traits::static_range{});
    }
  };
} } }

#endif
