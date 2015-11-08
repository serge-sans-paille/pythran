//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOINTS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/toints.hpp>
#include <boost/simd/include/functions/simd/toint.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/saturate.hpp>
#include <boost/simd/include/functions/simd/is_less_equal.hpp>
#include <boost/simd/include/functions/simd/is_greater_equal.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toints_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<uint_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(saturate<result_type>(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toints_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<int_<A0>,X>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    #ifdef BOOST_PROTO_STRICT_RESULT_OF
    result_type
    #else
    A0 const&
    #endif
    operator()(A0 const& a0) const
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toints_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type sr_t;
      static const A0 Vax = splat<A0>(boost::simd::Valmax<sr_t>());
      static const A0 Vix = splat<A0>(boost::simd::Valmin<sr_t>());
    #ifndef BOOST_SIMD_NO_NANS
      A0 aa0 = if_zero_else(is_nan(a0), a0);
      return if_else(boost::simd::le(aa0, Vix), Valmin<result_type>(),
                     if_else(boost::simd::ge(aa0, Vax), Valmax<result_type>(),
                             toint(aa0)
                            )
                    );
    #else
      return if_else(boost::simd::le(a0, Vix), Valmin<result_type>(),
                     if_else(boost::simd::ge(a0, Vax), Valmax<result_type>(),
                             toint(a0)
                            )
                    );
    #endif
    }
  };
} } }

#endif
