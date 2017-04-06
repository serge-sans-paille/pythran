//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_SHUFFLE_HPP_INCLUDED

#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  namespace detail
  {
    // ---------------------------------------------------------------------------------------------
    // Check if a permutation can use shuffle_p*
    template<int... Ps> struct avx_topology;

    template<int P0, int P1, int P2, int P3> struct avx_topology<P0,P1,P2,P3>
    {
      static const bool direct  = (P0<=1) && (P1==4||P1==5||P1==-1)
                                          && (P2==2||P2==3||P2==-1)
                                          && (P3==6||P3==7||P3==-1);

      static const bool indirect  =   (P0==4||P0==5||P0==-1)
                                  &&  (P1<=1)
                                  &&  (P2==6||P2==7||P2==-1)
                                  &&  (P3==2||P3==3||P3==-1);

      using type = typename std::conditional< direct
                                            , direct_<P0,P1,P2,P3>
                                            , typename std::conditional < indirect
                                                                        , indirect_<P0,P1,P2,P3>
                                                                        , pattern_<P0,P1,P2,P3>
                                                                        >::type
                                            >::type;
    };

    template<int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7>
    struct avx_topology<P0,P1,P2,P3,P4,P5,P6,P7>
    {
      static const bool direct  =  (             (         P0<= 4)                  || P0==-1)
                                && (             (         P1<= 4)                  || P1==-1)
                                && (             (P2>=8 && P2<=11)                  || P2==-1)
                                && (             (P3>=8 && P3<=11)                  || P3==-1)
                                && ( (P0==-1 &&  (P4>=4 && P4<= 7)) || (P4 == P0+4) || P4==-1)
                                && ( (P1==-1 &&  (P5>=4 && P5<= 7)) || (P5 == P1+4) || P5==-1)
                                && ( (P2==-1 &&  (P6>=12&& P6<=15)) || (P6 == P2+4) || P6==-1)
                                && ( (P3==-1 &&  (P7>=12&& P7<=15)) || (P7 == P3+4) || P7==-1);

      static const bool indirect  =  (             (         P2<= 4)                  || P2==-1)
                                  && (             (         P3<= 4)                  || P3==-1)
                                  && (             (P0>=8 && P0<=11)                  || P0==-1)
                                  && (             (P1>=8 && P1<=11)                  || P1==-1)
                                  && ( (P0==-1 &&  (P4>=12&& P4<=15)) || (P4 == P0+4) || P4==-1)
                                  && ( (P1==-1 &&  (P5>=12&& P5<=15)) || (P5 == P1+4) || P5==-1)
                                  && ( (P2==-1 &&  (P6>=4 && P6<= 7)) || (P6 == P2+4) || P6==-1)
                                  && ( (P3==-1 &&  (P7>=4 && P7<= 7)) || (P7 == P3+4) || P7==-1);

      using type =  typename
                    std::conditional< direct
                                    , direct_<P0,P1,P2,P3,P4,P5,P6,P7>
                                    , typename std::conditional < indirect
                                                                , indirect_<P0,P1,P2,P3,P4,P5,P6,P7>
                                                                , pattern_<P0,P1,P2,P3,P4,P5,P6,P7>
                                                                >::type
                                    >::type;
    };

    // ---------------------------------------------------------------------------------------------
    // AVX shuffling mask computation
    template<int P0,int P1, int P2, int P3>
    struct avx_mask_pd : tt::integral_constant<int, ((P3&1)<<3 | (P2&1)<<2 | (P1&1)<<1 | (P0&1))>
    {};

    template<int P0,int P1,int P2,int P3>
    struct avx_mask_ps : tt::integral_constant < int
                                                , ((P3&3)<<6 | (P2&3)<<4 | (P1&3)<<2 | (P0&3))
                                                >
    {};

    // ---------------------------------------------------------------------------------------------
    // AVX shuffling patterns
    struct shuffle_shuffle
    {
      // Binary shuffle permutation handler
      template<typename T,int P0,int P1,int P2,int P3>
      static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<P0,P1,P2,P3> const& p)
      {
        return shuff_(a0, a1, p, typename perform_zeroing<P0,P1,P2,P3>::type{});
      }

      template<typename T,int P0,int P1,int P2,int P3,int P4,int P5,int P6,int P7>
      static BOOST_FORCEINLINE T process( T const& a0, T const& a1
                                        , pattern_<P0,P1,P2,P3,P4,P5,P6,P7> const& p
                                        )
      {
        return shuff_(a0, a1, p, typename perform_zeroing<P0,P1,P2,P3,P4,P5,P6,P7>::type{});
      }

      // Masked binary shuffling
      template<typename T,int... Ps> static BOOST_FORCEINLINE
      T shuff_(const T& a0, const T & a1, pattern_<Ps...> const& p, tt::true_type const&)
      {
        using s_t  = typename T::value_type;
        using ui_t = boost::dispatch::as_integer_t<s_t,unsigned>;
        return  shuff_(a0,a1,p,tt::false_type{})
              & T ( bitwise_cast<s_t>(zeroing_mask<ui_t,Ps>::value)... );
      }

      // Regular binary shuffling
      template<typename T,int... Ps> static BOOST_FORCEINLINE
      T shuff_(const T& a0, const T & a1, pattern_<Ps...> const&, tt::false_type const&)
      {
        return shuff_(a0, a1, typename avx_topology<Ps...>::type{});
      }

      // Direct shuffling 64/32
      template<typename T,int P0,int P1,int P2,int P3> static BOOST_FORCEINLINE
      T shuff_(const T& a0, const T& a1, direct_<P0,P1,P2,P3> const&)
      {
        using f_t = bd::as_floating_t<T>;
        auto const v0 = bitwise_cast<f_t>(a0);
        auto const v1 = bitwise_cast<f_t>(a1);
        return bitwise_cast<T>(f_t(_mm256_shuffle_pd(v0, v1, (avx_mask_pd<P0,P1,P2,P3>::value))));
      }

      template<typename T,int P0,int P1,int P2,int P3,int P4,int P5,int P6,int P7>
      static BOOST_FORCEINLINE
      T shuff_(const T& a0, const T& a1, direct_<P0,P1,P2,P3,P4,P5,P6,P7> const&)
      {
        using f_t = bd::as_floating_t<T>;
        auto const v0 = bitwise_cast<f_t>(a0);
        auto const v1 = bitwise_cast<f_t>(a1);

        return bitwise_cast<T>(f_t(_mm256_shuffle_ps( v0, v1
                                                , (avx_mask_ps< P0 != -1 ? P0 : P4
                                                              , P1 != -1 ? P1 : P5
                                                              , P2 != -1 ? P2 : P6
                                                              , P3 != -1 ? P3 : P7
                                                   >::value)))
                              );
      }

      // Indirect shuffling is direct shuffling with a0/a1 permuted
      template<typename T,int... Ps> static BOOST_FORCEINLINE
      T shuff_(const T& a0, const T& a1, indirect_<Ps...> const&)
      {
        return shuff_(a1,a0,detail::direct_<Ps...>{});
      }

      // Mixed shuffling calls default matcher
      template<typename T,int... Ps> static BOOST_FORCEINLINE
      T shuff_(const T& a0, const T& a1, pattern_<Ps...> const& p)
      {
        return default_matcher::process(a0,a1,p);
      }
    };
  }
} }

#endif
