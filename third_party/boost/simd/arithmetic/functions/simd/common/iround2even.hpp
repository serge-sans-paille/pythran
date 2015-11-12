//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_IROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_IROUND2EVEN_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/iround2even.hpp>
#include <boost/simd/include/functions/simd/fast_iround2even.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::iround2even_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<single_<A0>, X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type sr_t;
      static const A0 Vax =  splat<A0>(boost::simd::Valmax<sr_t>());
      static const A0 Vix =  splat<A0>(boost::simd::Valmin<sr_t>());
    #ifndef BOOST_SIMD_NO_NANS
      A0 aa0 = if_zero_else(is_nan(a0), a0);
      return if_else(boost::simd::lt(aa0, Vix), Valmin<result_type>(),
                     if_else(boost::simd::gt(aa0, Vax), Valmax<result_type>(),
                             fast_iround2even(aa0)
                            )
                    );
    #else
      return if_else(boost::simd::lt(a0, Vix), Valmin<result_type>(),
                     if_else(boost::simd::gt(a0, Vax), Valmax<result_type>(),
                             fast_iround2even(a0)
                            )
                    );
    #endif
    }
  };
} } }


#endif
