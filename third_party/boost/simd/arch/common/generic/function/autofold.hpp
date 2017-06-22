//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_AUTOFOLD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_AUTOFOLD_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/splatted.hpp>
#include <boost/simd/detail/function/all_reduce.hpp>
#include <boost/simd/as.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_FALLBACK( ( typename F, typename BinOp, typename NeutralElement
                                    , typename Arg, typename Ext
                                    )
                                  , bd::reduction_<F,BinOp,NeutralElement>
                                  , bd::cpu_
                                  , bs::pack_<bd::unspecified_<Arg>, Ext>
                                  )
  {
    using result_t  = decltype( bd::functor<F>()( bd::detail::declval<typename Arg::value_type>() ) );
    using pr_t      = typename Arg::template rebind<result_t>;

    BOOST_FORCEINLINE result_t do_(Arg const& a0, aggregate_storage const&) const
    {
      bd::functor<F>      f;
      bd::functor<BinOp> op;

      return op( f(a0.storage()[0]), f(a0.storage()[1]));
    }

    template<typename K>
    BOOST_FORCEINLINE result_t do_(Arg const& a0, K const&) const
    {
      return extract<0> ( detail::all_reduce( bd::functor<BinOp>{}
                                            , bd::functor<NeutralElement>{}(as_<pr_t>{})
                                            , a0
                                            )
                        );
    }

    BOOST_FORCEINLINE result_t operator()(Arg const& a0) const
    {
      return do_( a0, typename Arg::traits::storage_kind{});
    }
  };

  BOOST_DISPATCH_OVERLOAD_FALLBACK( ( typename F, typename BinOp, typename NeutralElement
                                    , typename Arg, typename Ext
                                    )
                                  , bd::reduction_<F,BinOp,NeutralElement>
                                  , bd::cpu_
                                  , bs::splatted_tag
                                  , bs::pack_<bd::unspecified_<Arg>, Ext>
                                  )
  {
    using result_t  = decltype( bd::functor<F>()( bd::detail::declval<typename Arg::value_type>() ) );
    using pr_t      = typename Arg::template rebind<result_t>;


    BOOST_FORCEINLINE pr_t do_(Arg const& a0, aggregate_storage const&) const
    {
      bd::functor<F>      f;
      bd::functor<BinOp> op;

      auto r = op( splatted_(f)(a0.storage()[0]), splatted_(f)(a0.storage()[1]));
      return combine(r, r);
    }

    template<typename K>
    BOOST_FORCEINLINE pr_t do_(Arg const& a0, K const&) const
    {
      return  detail::all_reduce( bd::functor<BinOp>{}
                                , bd::functor<NeutralElement>{}(as_<pr_t>{})
                                , a0
                                );
    }

    BOOST_FORCEINLINE pr_t operator()(bs::splatted_tag const&, Arg const& a0) const
    {
      return do_( a0, typename Arg::traits::storage_kind{});
    }
  };
} } }

#endif
