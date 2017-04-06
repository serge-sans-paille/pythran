//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SLIDE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/hierarchy/exactly.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/detail/nsm.hpp>

#define BOOST_SIMD_UNARY_SLIDE(SZ,IDX)                                                              \
BOOST_DISPATCH_OVERLOAD ( slide_, (typename T), bs::avx_                                            \
                        , bs::pack_< bd::type##SZ##_<T>, bs::avx_ >                                 \
                          , bd::exactly_<nsm::type_traits::integral_constant<int,IDX>> \
                        )                                                                           \
/**/

#define BOOST_SIMD_BINARY_SLIDE(SZ,IDX)                                                             \
BOOST_DISPATCH_OVERLOAD ( slide_, (typename T), bs::avx_                                            \
                        , bs::pack_< bd::type##SZ##_<T>, bs::avx_ >                                 \
                        , bs::pack_< bd::type##SZ##_<T>, bs::avx_ >                                 \
                          , bd::exactly_<nsm::type_traits::integral_constant<int,IDX>> \
                        )                                                                           \
/**/

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  namespace tt = nsm::type_traits;

  // -----------------------------------------------------------------------------------------------
  // [64 bits] Unary exact matches for all cardinal to minimize latency and # of registers used
  // Thanks to Sylvain Jubertie for those tips
  BOOST_SIMD_UNARY_SLIDE(64,1)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,1> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_shuffle_pd(b0, _mm256_permute2f128_pd(b0, b0, 0x81), 0x5)));
    }
  };

  BOOST_SIMD_UNARY_SLIDE(64,2)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,2> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_permute2f128_pd(b0, b0, 0x81)));
    }
  };

  BOOST_SIMD_UNARY_SLIDE(64,3)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,3> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_shuffle_pd ( _mm256_permute2f128_pd(b0, b0, 0x81)
                                                    , bd::as_floating_t<T>(0)
                                                    , 0x1
                                                    )
                                )
                            );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // [64 bits] Binary exact matches for all cardinal to minimize latency and # of registers used
  // Thanks to Sylvain Jubertie for those tips
  BOOST_SIMD_BINARY_SLIDE(64,1)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,1> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      return bitwise_cast<T>(f_t( _mm256_shuffle_pd ( bitwise_cast<f_t>(a0)
                                                      , _mm256_permute2f128_pd( bitwise_cast<f_t>(a0)
                                                                              , bitwise_cast<f_t>(a1)
                                                                              , 0x21
                                                                              )
                                                      , 0x5
                                                      )
                                  )
                            );
    }
  };

  BOOST_SIMD_BINARY_SLIDE(64,2)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,2> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      return bitwise_cast<T>(f_t( _mm256_permute2f128_pd( bitwise_cast<f_t>(a0)
                                                    , bitwise_cast<f_t>(a1)
                                                    , 0x21
                                                    )
                                  )
                            );
    }
  };

  BOOST_SIMD_BINARY_SLIDE(64,3)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,3> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      return bitwise_cast<T>(f_t( _mm256_shuffle_pd ( _mm256_permute2f128_pd( bitwise_cast<f_t>(a0)
                                                                              , bitwise_cast<f_t>(a1)
                                                                              , 0x21
                                                                              )
                                                      , bitwise_cast<f_t>(a1)
                                                      , 0x5
                                                      )
                                  )
                            );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // [32 bits] Unary exact matches for all cardinal to minimize latency and # of registers used
  BOOST_SIMD_UNARY_SLIDE(32,1)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,1> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_permute_ps( _mm256_blend_ps( b0
                                                              , _mm256_permute2f128_ps(b0,b0,0x81)
                                                              , 0x11
                                                              )
                                              , 0x39
                                              )
                                 )
                            );
    }
  };

  BOOST_SIMD_UNARY_SLIDE(32,2)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,2> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_shuffle_ps(b0, _mm256_permute2f128_ps(b0, b0, 0x81), 0x4e) ));
    }
  };

  BOOST_SIMD_UNARY_SLIDE(32,3)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,3> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_permute_ps( _mm256_blend_ps( b0
                                                              , _mm256_permute2f128_ps(b0,b0,0x81)
                                                              , 0x77
                                                              )
                                              , 0x93
                                              )
                                 )
                            );
    }
  };

  BOOST_SIMD_UNARY_SLIDE(32,4)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,4> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_permute2f128_ps(b0,b0,0x81)));
    }
  };

  BOOST_SIMD_UNARY_SLIDE(32,5)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,5> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_permute_ps( _mm256_blend_ps (f_t(0)
                                                                , _mm256_permute2f128_ps(b0,b0,0x81)
                                                                , 0xe
                                                                )
                                              , 0x39
                                              )
                                 )
                            );
    }
  };

  BOOST_SIMD_UNARY_SLIDE(32,6)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,6> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_shuffle_ps( _mm256_permute2f128_ps(b0,b0,0x81 ), f_t(0), 0xe )));
    }
  };

  BOOST_SIMD_UNARY_SLIDE(32,7)
  {
    BOOST_FORCEINLINE T operator()( T const& a0
                                  , tt::integral_constant<int,7> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>(f_t( _mm256_permute_ps( _mm256_blend_ps (f_t(0)
                                                                , _mm256_permute2f128_ps(b0,b0,0x81)
                                                                , 0x8
                                                                )
                                              , 0x93
                                              )
                                 )
                            );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // [32 bits] Binary exact matches for all cardinal to minimize latency and # of registers used
  BOOST_SIMD_BINARY_SLIDE(32,1)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,1> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const b1 = bitwise_cast<f_t>(a1);

      return bitwise_cast<T>(f_t( _mm256_permute_ps
                                   ( _mm256_blend_ps ( b0
                                                     , _mm256_permute2f128_ps(b0,b1,0x21)
                                                     , 0x11
                                                     )
                                   , 0x39
                                   )
                                 )
                            );
    }
  };

  BOOST_SIMD_BINARY_SLIDE(32,2)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,2> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const b1 = bitwise_cast<f_t>(a1);

      return bitwise_cast<T>(f_t( _mm256_shuffle_ps(b0, _mm256_permute2f128_ps(b0,b1,0x21), 0x4e) ));
    }
  };

  BOOST_SIMD_BINARY_SLIDE(32,3)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,3> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const b1 = bitwise_cast<f_t>(a1);
      return bitwise_cast<T>(f_t( _mm256_permute_ps( _mm256_blend_ps ( b0
                                                                , _mm256_permute2f128_ps(b0,b1,0x21)
                                                                , 0x77
                                                                )
                                              , 0x93
                                                   )
                                 )
                            );
    }
  };

  BOOST_SIMD_BINARY_SLIDE(32,4)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,4> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      return bitwise_cast<T>(f_t( _mm256_permute2f128_ps(bitwise_cast<f_t>(a0),bitwise_cast<f_t>(a1),0x21)));
    }
  };

  BOOST_SIMD_BINARY_SLIDE(32,5)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,5> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const b1 = bitwise_cast<f_t>(a1);
      return bitwise_cast<T>(f_t( _mm256_permute_ps
                                   ( _mm256_blend_ps ( b1
                                                     , _mm256_permute2f128_ps(b0,b1,0x21)
                                                     , 0xee
                                                     )
                                   , 0x39
                                   )
                                  )
                            );
    }
  };

  BOOST_SIMD_BINARY_SLIDE(32,6)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,6> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const b1 = bitwise_cast<f_t>(a1);
      return bitwise_cast<T>(f_t( _mm256_shuffle_ps( _mm256_permute2f128_ps(b0,b1,0x21),b1,0x4e)));
    }
  };

  BOOST_SIMD_BINARY_SLIDE(32,7)
  {
    BOOST_FORCEINLINE T operator()( T const& a0, T const& a1
                                  , tt::integral_constant<int,7> const&
                                  ) const BOOST_NOEXCEPT
    {
      using f_t = bd::as_floating_t<T>;
      auto const b0 = bitwise_cast<f_t>(a0);
      auto const b1 = bitwise_cast<f_t>(a1);
      return bitwise_cast<T>(f_t( _mm256_permute_ps
                                   ( _mm256_blend_ps ( b1
                                                     , _mm256_permute2f128_ps(b0,b1,0x21)
                                                     , 0x88
                                                     )
                                   , 0x93
                                   )
                                 )
                            );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Reroute for small integers
  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename T, typename Offset)
                          , bs::avx_
                          , bs::pack_< bd::integer_<T>, bs::avx_ >
                          , bs::pack_< bd::integer_<T>, bs::avx_ >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    using hcard = tt::integral_constant<int,(T::static_size/2)>;

    static BOOST_FORCEINLINE T unroll( T const& a0, T const& a1, tt::true_type const& )
    {
      auto s0 = slice(a0);
      auto l1 = slice_low(a1);
      return combine( slide<Offset::value%hcard::value>(s0[0], s0[1])
                    , slide<Offset::value%hcard::value>(s0[1], l1)
                    );
    }

    static BOOST_FORCEINLINE T unroll( T const& a0, T const& a1, tt::false_type const& )
    {
      auto s1 = slice(a1);
      auto h0 = slice_high(a0);
      return combine( slide<Offset::value%hcard::value>(h0   , s1[0])
                    , slide<Offset::value%hcard::value>(s1[0], s1[1])
                    );
    }

    BOOST_FORCEINLINE T operator()(T const& a0, T const& a1, Offset const&) const
    {
      return unroll ( a0, a1
                    , nsm::bool_<(Offset::value < hcard::value)>{}
                    );
    }
  };


  // -----------------------------------------------------------------------------------------------
  // Reroute for logical
  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename T, typename Offset)
                          , bs::avx_
                          , bs::pack_< bs::logical_<T>, bs::avx_ >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T const& a0, Offset const&) const BOOST_NOEXCEPT
    {
      return bitwise_cast<T>( slide<Offset::value>( genmask(a0) ) );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename T, typename Offset)
                          , bs::avx_
                          , bs::pack_< bs::logical_<T>, bs::avx_ >
                          , bs::pack_< bs::logical_<T>, bs::avx_ >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T const& a0, T const& a1, Offset const&) const BOOST_NOEXCEPT
    {
      return bitwise_cast<T>( slide<Offset::value>( genmask(a0), genmask(a1) ) );
    }
  };
} } }

#endif
