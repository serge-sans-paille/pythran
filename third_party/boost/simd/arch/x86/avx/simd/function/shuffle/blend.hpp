//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_BLEND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_BLEND_HPP_INCLUDED

#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  // -----------------------------------------------------------------------------------------------
  // Shuffle using blend patterns hierarchy
  template<bool HasZero, typename P> struct blend_pattern : P
  {
    using parent = P;
  };

  namespace detail
  {
    // ---------------------------------------------------------------------------------------------
    // Check if a permutation can use blend_p*
    template<int... Ps> struct is_blend;

    template<int P0, int P1, int P2, int P3> struct is_blend<P0,P1,P2,P3>
    {
      static const bool regular =   (P0==0  || P0==4 ) && (P1==1  || P1==5 )
                                &&  (P2==2  || P2==6 ) && (P3==3  || P3==7 );

      static const bool left_z =    (P0==0  || P0==-1) && (P1==1  || P1==-1)
                                &&  (P2==2  || P2==-1) && (P3==3  || P3==-1);

      static const bool right_z =   (P0==-1 || P0==4 ) && (P1==-1 || P1==5 )
                                &&  (P2==-1 || P2==6 ) && (P3==-1 || P3==7 );

      static const bool value = regular || left_z || right_z;
      using mode = blend_pattern<left_z || right_z, pattern_<P0,P1,P2,P3>>;
    };


    template<int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7>
    struct is_blend<P0,P1,P2,P3,P4,P5,P6,P7>
    {
      static const bool regular =   (P0==0  || P0==8 ) && (P1==1  || P1==9 )
                                &&  (P2==2  || P2==10) && (P3==3  || P3==11)
                                &&  (P4==4  || P4==12) && (P5==5  || P5==13)
                                &&  (P6==6  || P6==14) && (P7==7  || P7==15);

      static const bool left_z =    (P0==0  || P0==-1) && (P1==1  || P1==-1)
                                &&  (P2==2  || P2==-1) && (P3==3  || P3==-1)
                                &&  (P4==4  || P4==-1) && (P5==5  || P5==-1)
                                &&  (P6==6  || P6==-1) && (P7==7  || P7==-1);

      static const bool right_z =   (P0==-1 || P0==8 ) && (P1==-1 || P1==9 )
                                &&  (P2==-1 || P2==10) && (P3==-1 || P3==11)
                                &&  (P4==-1 || P4==12) && (P5==-1 || P5==13)
                                &&  (P6==-1 || P6==14) && (P7==-1 || P7==15);

      static const bool value = regular || left_z || right_z;
      using mode = blend_pattern<left_z || right_z, pattern_<P0,P1,P2,P3,P4,P5,P6,P7>>;
    };

    // ---------------------------------------------------------------------------------------------
    // Prevent ambiguity with other hierarchy
    template<> struct is_blend<-1,-1,-1,-1> : tt::false_type {};
    template<> struct is_blend< 0, 1, 2, 3> : tt::false_type {};
    template<> struct is_blend< 4, 5, 6, 7> : tt::false_type {};
    template<> struct is_blend< 0,-1, 2,-1> : tt::false_type {};
    template<> struct is_blend<-1, 1,-1, 3> : tt::false_type {};

    template<> struct is_blend<-1,-1,-1,-1,-1,-1,-1,-1> : tt::false_type {};
    template<> struct is_blend< 0, 1, 2, 3, 4, 5, 6, 7> : tt::false_type {};
    template<> struct is_blend< 8, 9,10,11,12,13,14,15> : tt::false_type {};
    template<> struct is_blend< 0,-1, 2,-1, 4,-1, 6,-1> : tt::false_type {};
    template<> struct is_blend<-1, 1,-1, 3,-1, 5,-1, 7> : tt::false_type {};

    // ---------------------------------------------------------------------------------------------
    // Compute the blend mask to use
    template<typename P> struct blend_mask;

    template<int P0, int P1, int P2, int P3>
    struct  blend_mask<pattern_<P0,P1,P2,P3>>
          : tt::integral_constant< int
                                  , (P0==4 || P0==-1)    | (P1==5 || P1==-1)<<1
                                  | (P2==6 || P2==-1)<<2 | (P3==7 || P3==-1)<<3
                                  >
    {};

    template<int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7>
    struct  blend_mask<pattern_<P0,P1,P2,P3,P4,P5,P6,P7>>
          : tt::integral_constant< int
                                  , (P0==8  || P0==-1)    | (P1==9  || P1==-1)<<1
                                  | (P2==10 || P2==-1)<<2 | (P3==11 || P3==-1)<<3
                                  | (P4==12 || P4==-1)<<4 | (P5==13 || P5==-1)<<5
                                  | (P6==14 || P6==-1)<<6 | (P7==15 || P7==-1)<<7
                                  >
    {};

    // ---------------------------------------------------------------------------------------------
    // AVX shuffling patterns
    struct blend_shuffle
    {
      // Blend permutation handler
      template<typename T, typename P>
      static BOOST_FORCEINLINE T process(T const& a0, blend_pattern<true,P> const&)
      {
        using f_t = bd::as_floating_t<T>;
        return bitwise_cast<T>( blend_( bitwise_cast<f_t>(a0), Zero<f_t>()
                                      , P{}, typename P::size_type{}
                                      )
                              );
      }

      template<typename T, typename P>
      static BOOST_FORCEINLINE T process(T const& a0, T const& a1, blend_pattern<false,P> const&)
      {
        using f_t = bd::as_floating_t<T>;
        return bitwise_cast<T>( blend_( bitwise_cast<f_t>(a0), bitwise_cast<f_t>(a1)
                                      , P{}, typename P::size_type{}
                                      )
                              );
      }

      template<typename T, typename P>
      static BOOST_FORCEINLINE T blend_ ( T const& a0, T const& a1, P const&
                                        , tt::integral_constant<std::size_t,4> const&
                                        )
      {
        return _mm256_blend_pd(a0, a1, blend_mask<P>::value);
      }

      template<typename T, typename P>
      static BOOST_FORCEINLINE T blend_ ( T const& a0, T const& a1, P const&
                                        , tt::integral_constant<std::size_t,8> const&
                                        )
      {
        return _mm256_blend_ps(a0, a1, blend_mask<P>::value);
      }
    };
  }
} }

// -------------------------------------------------------------------------------------------------
// Hierarchize blend patterns
namespace boost { namespace dispatch { namespace ext
{
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if<simd::detail::is_blend<Ps...>::value>::type
                          >
  {
    using type = typename simd::detail::is_blend<Ps...>::mode;
  };
} } }

#endif
