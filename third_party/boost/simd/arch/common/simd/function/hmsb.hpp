//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_HMSB_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/bitset.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD(hmsb_
                        , (typename A0, typename X)
                        , bd::cpu_
                        , bs::pack_<bd::arithmetic_<A0>, X>
                        )
  {
    using result_t = bs::bitset<cardinal_of<A0>::value>;

    template<typename I> BOOST_FORCEINLINE void piece(const A0& a0, result_t& r) const BOOST_NOEXCEPT
    {
      r.set ( I::value
            , bs::bitwise_and ( bs::Signmask<bd::as_integer_t<typename A0::value_type>>()
                              , bs::extract<I::value>(a0)
                              ) != 0
            );
    }

    template<typename... N>
    BOOST_FORCEINLINE void do_(const A0& a0, result_t& r, nsm::list<N...> const&) const BOOST_NOEXCEPT
    {
      (void)(std::initializer_list<bool>{(piece<N>(a0,r),true)...});
    }

    BOOST_FORCEINLINE result_t operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      result_t r;
      do_(a0,r,typename A0::traits::element_range());
      return r;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( hmsb_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bs::logical_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE bs::bitset<cardinal_of<A0>::value> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return bs::hmsb(bs::genmask(a0));
    }
  };
} } }

#endif
