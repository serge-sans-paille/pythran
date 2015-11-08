//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_SSE_LOG10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_SSE_LOG10_HPP_INCLUDED
#if defined(BOOST_SIMD_HAS_SSE2_SUPPORT)

#include <nt2/exponential/functions/log10.hpp>
#include <nt2/include/functions/simd/make.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sum.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/assert.hpp>

#include <boost/simd/sdk/simd/native.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_
                                   , boost::simd::tag::sse_
                                   , (A0)
                                   , (scalar_< int_<A0> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0, unsigned>::type ui_type;
      BOOST_ASSERT_MSG( a0 > 0, "log10 is not defined for zero or negative integers." );
      return result_type(log10(ui_type(a0)));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, boost::simd::tag::sse_
                            , (A0)
                            , (scalar_< uint32_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef boost::simd::native<int32_t,  boost::simd::tag::sse_> v_type;
      v_type va0 = splat<v_type>(a0);
      v_type t2 = make<v_type>(99999999, 9999999, 999999, 99999);
      if (a0 > 999999999) return 9;
      if (a0 > 99999) return 4-sum(bitwise_cast<v_type>(gt(va0, t2)));
      v_type t1 = make<v_type>(9999, 999, 99, 9);
      return -sum(bitwise_cast<v_type>(gt(va0, t1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, boost::simd::tag::sse_
                            , (A0)
                            , (scalar_< uint64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef boost::simd::native<int32_t,  boost::simd::tag::sse_> v_type;
      v_type t2 = make<v_type>(99999999, 9999999, 999999, 99999);
      if (a0 >99999999999999999ull)
      {
        v_type va0 = splat<v_type>(a0/1000000000000ull);
        return 16-sum(bitwise_cast<v_type>(gt(va0, t2)));
      }
      if (a0 >9999999999999ull)
      {
        v_type va0 = splat<v_type>(a0/100000000ull);
        return 12-sum(bitwise_cast<v_type>(gt(va0, t2)));
      }
      if (a0 >999999999ull)
      {
        v_type va0 =  splat<v_type>(a0/10000ull);
        return 8-sum(bitwise_cast<v_type>(gt(va0, t2)));
      }

      v_type va0 = splat<v_type>(a0);

      if (a0 >99999ull)
      {
        return 4-sum(bitwise_cast<v_type>(gt(va0, t2)));
      }

      v_type t1 = make<v_type>(9999, 999, 99, 9);
      return -sum(bitwise_cast<v_type>(gt(va0, t1)));
    }
  };

} }

#endif
#if defined(BOOST_SIMD_HAS_AVX_SUPPORT)

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_,  boost::simd::tag::avx_
                            , (A0)
                            , (scalar_< uint32_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef boost::simd::native<int32_t, boost::simd::tag::avx_> v_type;
      if (a0 > 999999999) return 9;
      v_type va0 = splat<v_type>(a0);
      v_type t = make<v_type>(99999999, 9999999, 999999, 99999, 9999, 999, 99, 9);
      return -sum(bitwise_cast<v_type>(gt(va0, t)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_,  boost::simd::tag::avx_
                            , (A0)
                            , (scalar_< uint64_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef boost::simd::native<int32_t, boost::simd::tag::avx_> v_type_0;
      typedef boost::simd::native<int32_t, boost::simd::tag::sse_> v_type_1;
      v_type_1 t2 = make<v_type_1>(99999999, 9999999, 999999, 99999);
      if (a0 >99999999999999999ull)
      {
        v_type_1 va0 = splat<v_type_1>(a0/1000000000000ull);
        return 16-sum(bitwise_cast<v_type_1>(gt(va0, t2)));
      }
      v_type_0 t1 = make<v_type_0>(99999999, 9999999, 999999, 99999, 9999, 999, 99, 9);
      if (a0 >999999999ull)
      {
        v_type_0 va0 = splat<v_type_0>(a0/100000000ull);
        return 8-sum(bitwise_cast<v_type_0>(gt(va0, t1)));
      }
      v_type_0 va0 = splat<v_type_0>(a0);
      return -sum(bitwise_cast<v_type_0>(gt(va0, t1)));
    }
  };
} }


#endif

#endif
