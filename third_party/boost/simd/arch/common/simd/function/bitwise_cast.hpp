//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  namespace tt = nsm::type_traits;

  BOOST_DISPATCH_OVERLOAD_IF ( bitwise_cast_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::arithmetic_<A0>, X>
                             , bd::target_< bs::pack_< bs::logical_<A1>, X> >
                             )
  {
    using result_t =  typename A1::type;

    static_assert ( (sizeof(A0) == sizeof(result_t))
                  , "boost.simd target is not same size as source in bitwise_cast"
                  );

    BOOST_FORCEINLINE result_t operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      using a_t = bs::as_arithmetic_t<result_t>;
      return bitwise_cast<a_t>(a0).storage();
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( bitwise_cast_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bs::logical_<A0>, X >
                             , bd::target_< bs::pack_< bd::arithmetic_<A1>, X > >
                             )
  {
    using result_t =  typename A1::type;

    static_assert ( (sizeof(A0) == sizeof(result_t))
                  , "boost.simd target is not same size as source in bitwise_cast"
                  );

    BOOST_FORCEINLINE result_t operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      using a_t = bs::as_arithmetic_t<A0>;
      a_t tmp{a0.storage()};
      return bitwise_cast<result_t>(tmp);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( bitwise_cast_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bs::logical_<A0>, X >
                             , bd::target_< bs::pack_< bs::logical_<A1>, X > >
                             )
  {
    using result_t =  typename A1::type;

    static_assert ( (sizeof(A0) == sizeof(result_t))
                  , "boost.simd target is not same size as source in bitwise_cast"
                  );

    BOOST_FORCEINLINE result_t operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return do_(a0, typename tt::is_same<A0, result_t>::type());
    }

    BOOST_FORCEINLINE result_t do_(A0 const& a0, tt::false_type ) const BOOST_NOEXCEPT
    {
      using a_t = bs::as_arithmetic_t<A0>;
      using r_t = bs::as_arithmetic_t<result_t>;
      return bitwise_cast<r_t>(bitwise_cast<a_t>(a0)).storage() ;
    }

    BOOST_FORCEINLINE result_t do_(A0 const& a0, tt::true_type const& ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
} } }

#endif
