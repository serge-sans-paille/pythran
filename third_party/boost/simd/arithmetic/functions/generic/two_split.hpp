//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_TWO_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_TWO_SPLIT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/two_split.hpp>
#include <boost/simd/include/constants/splitfactor.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/sdk/config/enforce_precision.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_split_
                                    , tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,A0& a2) const
    {
      result_type a1;
      boost::simd::two_split(a0, a1, a2);
      return a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_split_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                    )
  {
    typedef std::pair<A0,A0>                                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 first, second;
      boost::simd::two_split( a0, first, second );
      return result_type(first, second);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_split_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a, A0 & r0,A0 & r1) const
    {
      boost::simd::config::enforce_precision<A0> enforcer;
      A0 const c = boost::simd::Splitfactor<A0>()*a;
      A0 const c1 = c-a;
      r0 = c-c1;
      r1 = a-r0;
    }
  };
} } }

#endif
