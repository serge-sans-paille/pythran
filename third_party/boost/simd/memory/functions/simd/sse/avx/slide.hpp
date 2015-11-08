//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_SLIDE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/memory/functions/slide.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::avx_
                                    , (A0)(N)
                                    , ((simd_< arithmetic_<A0>
                                            , boost::simd::tag::avx_
                                            >
                                      ))
                                      (mpl_integral_< scalar_< integer_<N> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, N const&) const
    {
      return eval ( a0
                  , boost::mpl::bool_<N::value==0>()
                  , boost::mpl::bool_ <   (N::value ==  A0::static_size)
                                      ||  (N::value == -A0::static_size)
                                      >()
                  );
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0
                    , boost::mpl::true_ const&, boost::mpl::false_ const&
                    ) const
    {
      return a0;
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const&
                    , boost::mpl::false_ const&, boost::mpl::true_ const&
                    ) const
    {
      return Zero<A0>();
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0
                    , boost::mpl::false_ const&, boost::mpl::false_ const&
                    ) const
    {
      return eval(a0, mpl::bool_<(N::value>=0)>());
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, boost::mpl::true_ const& ) const
    {
      return slide<N::value>(a0,Zero<A0>());
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, boost::mpl::false_ const& ) const
    {
      return slide<A0::static_size+N::value>(Zero<A0>(),a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::avx_
                                    , (A0)(N)
                                    , ((simd_< arithmetic_<A0>
                                            , boost::simd::tag::avx_
                                            >
                                      ))
                                      ((simd_< arithmetic_<A0>
                                            , boost::simd::tag::avx_
                                            >
                                      ))
                                      (mpl_integral_< scalar_< integer_<N> > >)
                                    )
  {
    typedef A0 result_type;

    typedef typename meta::retarget<A0,tag::sse_>::type sub_t;
    typedef typename A0::template rebind<unsigned char>::type u8type;
    typedef typename sub_t::template rebind<unsigned char>::type u8subtype;
    static const int hcard = A0::static_size / 2;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, N const&) const
    {
      return side ( a0, a1
                  , boost::mpl::bool_< (N::value>=0) >()
                  );
    }

    BOOST_FORCEINLINE
    result_type side(A0 const& a0, A0 const& a1, boost::mpl::true_ const&) const
    {
      return eval ( a0, a1
                  , boost::mpl::bool_<N::value==0>()
                  , boost::mpl::bool_<N::value==A0::static_size>()
                  );
    }

    BOOST_FORCEINLINE
    result_type side(A0 const& a0, A0 const& a1, boost::mpl::false_ const&) const
    {
      return slide<A0::static_size + N::value>(a1,a0);
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, A0 const&
                    , boost::mpl::true_ const&, boost::mpl::false_ const&
                    ) const
    {
      return a0;
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const&, A0 const& a1
                    , boost::mpl::false_ const&, boost::mpl::true_ const&
                    ) const
    {
      return a1;
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, A0 const& a1
                    , boost::mpl::false_ const&, boost::mpl::false_ const&
                    ) const
    {
      return eval ( bitwise_cast<u8type>(a1)
                  , bitwise_cast<u8type>(a0)
                  , boost::mpl::bool_<(N::value < hcard)>()
                  );
    }

    BOOST_FORCEINLINE
    result_type eval(__m256i v0, __m256i v1, boost::mpl::true_ const&) const
    {
      u8subtype v0h = _mm256_extractf128_si256(v0, 0);
      u8subtype v1h = _mm256_extractf128_si256(v1, 0);
      u8subtype v1l = _mm256_extractf128_si256(v1, 1);

      sub_t s0h = bitwise_cast<sub_t>(v0h);
      sub_t s1h = bitwise_cast<sub_t>(v1h);
      sub_t s1l = bitwise_cast<sub_t>(v1l);

      s1h = slide<N::value%hcard>(s1h, s1l);
      s0h = slide<N::value%hcard>(s1l, s0h);

      u8type that = _mm256_castsi128_si256(bitwise_cast<u8subtype>(s1h));
      that = _mm256_insertf128_si256(that, bitwise_cast<u8subtype>(s0h), 1);

      return bitwise_cast<result_type>(that);
    }

    BOOST_FORCEINLINE
    result_type eval(__m256i v0, __m256i v1, boost::mpl::false_ const&) const
    {
      u8subtype v0l = _mm256_extractf128_si256(v0, 1);
      u8subtype v0h = _mm256_extractf128_si256(v0, 0);
      u8subtype v1l = _mm256_extractf128_si256(v1, 1);

      sub_t s0l = bitwise_cast<sub_t>(v0l);
      sub_t s0h = bitwise_cast<sub_t>(v0h);
      sub_t s1l = bitwise_cast<sub_t>(v1l);

      s1l = slide<N::value%hcard>(s1l, s0h);
      s0l = slide<N::value%hcard>(s0h, s0l);

      u8type that = _mm256_castsi128_si256(bitwise_cast<u8subtype>(s1l));
      that = _mm256_insertf128_si256(that, bitwise_cast<u8subtype>(s0l), 1);

      return bitwise_cast<result_type>(that);
    }
  };
} } }

#endif
#endif
