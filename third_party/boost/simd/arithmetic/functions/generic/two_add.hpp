//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_TWO_ADD_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_TWO_ADD_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/two_add.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/is_inf.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/config/enforce_precision.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_add_
                                    , tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,A0 const& a1,A0& a3) const
    {
      result_type a2;
      boost::simd::two_add(a0, a1, a2, a3);
      return a2;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_add_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef std::pair<A0,A0>                                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 const& a1) const
    {
      A0 first, second;
      boost::simd::two_add( a0, a1, first, second );
      return result_type(first, second);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_add_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE
    result_type operator()(A0 const& a,A0 const& b, A0 & r0,A0 & r1) const
    {
      boost::simd::config::enforce_precision<A0> enforcer;
      r0   = a  + b;
      A0 z = r0 - a;
#if defined(BOOST_SIMD_NO_INFINITIES)
      r1   = a-(r0-z)+(b-z);
#else
      r1   = if_zero_else(is_inf(r0), (a-(r0-z))+(b-z));
#endif
    }
  };
} } }

#endif
