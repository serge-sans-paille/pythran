//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SATURATE_HPP_INCLUDED

#include <boost/simd/as.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  // floating -> floating
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( saturate_
                          , (typename A0, typename T)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::target_< bd::scalar_< bd::floating_<T> > >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, T ) const BOOST_NOEXCEPT
    {
      return impl( a0
                   , nsm::bool_< (sizeof(bd::scalar_of_t<typename T::type>)
                                             <sizeof(bd::scalar_of_t<A0>))>()
                   );
    }

    BOOST_FORCEINLINE A0 impl( A0 a0
                                        , const tt::true_type &) const BOOST_NOEXCEPT
    {
      using starget_t = bd::scalar_of_t<typename T::type>;
      const A0 vma = splat<A0>(Valmax<starget_t>());
      const A0 vmi = splat<A0>(Valmin<starget_t>());
      return (is_inf(a0)? a0: min(vma, max(vmi, a0)));
    }
    BOOST_FORCEINLINE A0 impl( A0 a0
                                             , const tt::false_type &) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  // floating -> integer
  BOOST_DISPATCH_OVERLOAD ( saturate_
                          , (typename A0, typename T)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::target_< bd::scalar_< bd::floating_<T> > >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, T ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( saturate_
                          , (typename A0, typename T)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::target_< bd::scalar_< bd::arithmetic_<T> > >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, T ) const BOOST_NOEXCEPT
    {
      return impl( a0
                   , typename nsm::or_< typename std::is_same< bd::scalar_of_t<typename T::type>
                                                         , bd::scalar_of_t<A0>
                                                        >::type
                                           , nsm::bool_< (sizeof(bd::scalar_of_t<typename T::type>)
                                                             > sizeof(bd::scalar_of_t<A0>))
                                                           >
                                          >::type()
                   );
    }
    static BOOST_FORCEINLINE A0 impl( A0 a0
                                        , const tt::true_type &) BOOST_NOEXCEPT
    {
      return a0;
    }
    static BOOST_FORCEINLINE A0 impl( A0 a0
                                        , const tt::false_type &) BOOST_NOEXCEPT
    {
      using starget_t = bd::scalar_of_t<typename T::type>;
      const A0 vma = splat<A0>(Valmax<starget_t>());
      const A0 vmi = splat<A0>(Valmin<starget_t>());
      return min(vma, max(vmi, a0));
    }
  };

  // signed saturated by unsigned just test for negative and Valmax of signed
  BOOST_DISPATCH_OVERLOAD ( saturate_
                          , (typename A0, typename T)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          , bd::target_< bd::scalar_< bd::unsigned_<T> > >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, T ) const BOOST_NOEXCEPT
    {
      return impl( a0
                   , nsm::bool_< (sizeof(bd::scalar_of_t<typename T::type>)
                                      >= sizeof(bd::scalar_of_t<A0>))
                                   >()
                   );
    }
    static BOOST_FORCEINLINE A0 impl( A0 a0
                                        , const tt::true_type &) BOOST_NOEXCEPT
    {
      return max(Zero<A0>(), a0);
    }
    static BOOST_FORCEINLINE A0 impl( A0 a0
                                        , const tt::false_type &) BOOST_NOEXCEPT
    {
      using starget_t = bd::scalar_of_t<typename T::type>;
      const A0 vma = splat<A0>(Valmax<starget_t>());
      return min(vma, max(Zero<A0>(), a0));
    }
  };

  // unsigned saturated by signed just test for greater than Valmax of signed
  BOOST_DISPATCH_OVERLOAD ( saturate_
                          , (typename A0, typename  T)
                          , bd::cpu_
                          , bd::scalar_<bd::unsigned_<A0> >
                          , bd::target_< bd::scalar_< bd::integer_<T> > >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (  A0 a0, T ) const BOOST_NOEXCEPT
    {
      using starget_t = bd::scalar_of_t<typename T::type>;
      A0 vma = splat<A0>(Valmax<starget_t>());
      return min(vma, a0);
    }
  };

   // unsigned saturated by unsigned just test for greater than Valmax
  BOOST_DISPATCH_OVERLOAD ( saturate_
                          , (typename A0, typename  T)
                          , bd::cpu_
                          , bd::scalar_<bd::unsigned_<A0> >
                          , bd::target_< bd::scalar_< bd::unsigned_<T> > >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, T ) const BOOST_NOEXCEPT
    {
      return impl( a0
                   , nsm::bool_< (sizeof(bd::scalar_of_t<typename T::type>)
                                      >= sizeof(bd::scalar_of_t<A0>))
                                   >()
                   );
    }
    static BOOST_FORCEINLINE A0 impl( A0 a0
                                        , const tt::true_type &) BOOST_NOEXCEPT
    {
      return a0;
    }
    static BOOST_FORCEINLINE A0 impl( A0 a0
                                        , const tt::false_type &) BOOST_NOEXCEPT
    {
      using starget_t = bd::scalar_of_t<typename T::type>;
      const A0 vma = splat<A0>(Valmax<starget_t>());
      return min(vma, a0);
    }
  };
} } }


#endif
