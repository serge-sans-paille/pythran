//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_TWO_PROD_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_TWO_PROD_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/two_prod.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/two_split.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/is_invalid.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/config/enforce_precision.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_prod_
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
      boost::simd::two_prod(a0, a1, a2, a3);
      return a2;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_prod_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef std::pair<A0,A0>                                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 const& a1) const
    {
      A0 first, second;
      boost::simd::two_prod( a0, a1, first, second );
      return result_type(first, second);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::two_prod_, tag::cpu_
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

      A0 a1, a2, b1, b2;
      r0  = a*b;

      two_split(a, a1, a2);
      two_split(b, b1, b2);

#if defined(BOOST_SIMD_NO_INVALIDS)
      r1 = a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2);
#else
      r1 = if_zero_else(is_invalid(r0), a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2));
#endif

    }
  };
} } }

#endif
