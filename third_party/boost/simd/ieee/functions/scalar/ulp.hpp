//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_ULP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_ULP_HPP_INCLUDED

#include <boost/simd/ieee/functions/ulp.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/functions/scalar/prev.hpp>
#include <boost/simd/include/functions/scalar/min.hpp>
#include <boost/simd/include/functions/scalar/is_eqz.hpp>
#include <boost/simd/include/functions/scalar/is_invalid.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mindenormal.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulp_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const &)const
    {
      return One<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulp_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type int_type;
      if (is_eqz(a0)) return Mindenormal<A0>();
      if (is_invalid(a0)) return Nan<A0>();
      const A0 x = boost::simd::abs(a0);
      int_type aa = bitwise_cast<int_type>(x);
      int_type bb = aa;
      --bb;
      ++aa;
      return boost::simd::min(x-bitwise_cast<A0>(bb), bitwise_cast<A0>(aa)-x);
    }
  };
} } }

#endif
