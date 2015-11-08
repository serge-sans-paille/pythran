//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SAFE_MAX_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SAFE_MAX_HPP_INCLUDED

#include <boost/simd/ieee/functions/safe_max.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/constants/sqrtvalmax.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/predicates/functions/is_nez.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::safe_max_, tag::cpu_
                                    , (A0), (generic_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else(is_nez(a0), Sqrtvalmax<A0>()/boost::simd::abs(a0), Inf<result_type>());
    }
  };
} } }

#endif
