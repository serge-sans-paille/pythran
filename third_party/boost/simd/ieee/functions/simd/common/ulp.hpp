//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_ULP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_ULP_HPP_INCLUDED
#include <boost/simd/ieee/functions/ulp.hpp>

#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/ieee/functions/simd/common/details/ulp.hpp>
#include <boost/dispatch/attributes.hpp>

#if defined(BOOST_SIMD_NO_DENORMALS)
#include <boost/simd/include/functions/simd/ldexp.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/include/constants/mindenormal.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulp_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0&)const
    {
      return One<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulp_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const A0 x = boost::simd::abs(a0);

      #if !defined(BOOST_SIMD_NO_DENORMALS)

      return details::ulp(x);

      #else

      typedef typename dispatch::meta::as_integer<A0>::type in_t;
      const in_t n = simd::Nbmantissabits<A0>();

      return if_else( is_eqz(x)
                    , Mindenormal<A0>()
                    , if_else ( x < simd::Smallestposval<A0>()
                              , simd::ldexp ( details::ulp(simd::ldexp(x,n))
                                            , -n
                                            )
                              , details::ulp(x)
                              )
                    );
      #endif
    }
  };

} } }

#endif
