//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_ARG_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_ARG_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/arg.hpp>
#include <boost/simd/include/constants/pi.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/if_allbits_else.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arg_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      // a0 >= 0 -> 0, a0 < 0 ->Pi, a0 is Nan -> Nan
      result_type r = if_else_zero(is_ltz(a0),Pi<result_type>());
      #ifndef BOOST_SIMD_NO_NANS
        return if_nan_else(is_nan(a0),r);
      #else
        return r;
      #endif
    }
  };
} } }

#endif
