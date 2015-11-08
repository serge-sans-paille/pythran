//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_MANTISSA_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_MANTISSA_HPP_INCLUDED

#include <boost/simd/ieee/functions/mantissa.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mantissamask.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/bitwise_or.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/include/functions/simd/is_invalid.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mantissa_, tag::cpu_
                                    , (A0)
                                    , (scalar_< integer_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mantissa_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if(!a0) return a0;
      #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_invalid(a0)) return a0;
      #endif
      return b_or(b_and(a0,Mantissamask<A0>()),One<A0>());
    }
  };
} } }


#endif
