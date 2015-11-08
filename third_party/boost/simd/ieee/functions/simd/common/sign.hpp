//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_SIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_SIGN_HPP_INCLUDED

#include <boost/simd/ieee/functions/sign.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/is_gtz.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/functions/simd/shift_right.hpp>
#include <boost/simd/include/functions/simd/if_one_else_zero.hpp>
#include <boost/simd/include/functions/simd/if_allbits_else.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sign_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      return shrai(a0, sizeof(sA0)*8-1)-shrai(-a0, sizeof(sA0)*8-1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sign_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<unsigned_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return if_one_else_zero(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sign_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 r = if_one_else_zero(is_gtz(a0))-if_one_else_zero(is_ltz(a0));
      #ifdef BOOST_SIMD_NO_NANS
      return r;
      #else
      return if_allbits_else(is_nan(a0), r);
      #endif
    }
  };
} } }
#endif
