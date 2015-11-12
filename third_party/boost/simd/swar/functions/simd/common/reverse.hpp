//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_REVERSE_HPP_INCLUDED

#include <boost/simd/swar/functions/reverse.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/is_bitwise_logical.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/preprocessor/make.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< arithmetic_<A0>, X>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return eval(a0,typename simd::meta::cardinal_of<result_type>::type());
    }

    #define M0(z, n, t) extract<meta::cardinal_of<A0>::value-1-n>(a0)

    BOOST_SIMD_PP_IMPLEMENT_WITH_MAKE(1, M0)

    #undef M0
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::reverse_, tag::cpu_
                                      , (A0)(X)
                                      , ( boost::simd::meta::is_bitwise_logical<A0> )
                                      , ((simd_< logical_<A0>, X>))
                                      )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_arithmetic<A0>::type type;
      return bitwise_cast<result_type>(
        reverse( bitwise_cast<type>(a0) )
      );
    }
  };
} } }

#endif
