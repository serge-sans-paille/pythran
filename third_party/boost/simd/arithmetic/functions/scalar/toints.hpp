//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_TOINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_TOINTS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/toints.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/functions/scalar/saturate.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/simd/sdk/config.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toints_, tag::cpu_
                                    , (A0)
                                    , (scalar_< int_<A0> >)
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
                                    , (A0)
                                    , (scalar_< uint_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(saturate<result_type>(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toints_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
    #ifndef BOOST_SIMD_NO_NANS
      if (boost::simd::is_nan(a0))       return Zero<result_type>();
    #endif
      if (a0 >= Valmax<result_type>())   return Valmax<result_type>();
      if (a0 <= Valmin<result_type>())   return Valmin<result_type>();
      return result_type(a0);
    }
  };
} } }

#endif
