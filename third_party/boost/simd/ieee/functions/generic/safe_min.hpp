//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SAFE_MIN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_GENERIC_SAFE_MIN_HPP_INCLUDED

#include <boost/simd/ieee/functions/safe_min.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/constants/sqrtsmallestposval.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::safe_min_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return Sqrtsmallestposval<A0>()*boost::simd::abs(a0);
    }
  };
} } }


#endif
