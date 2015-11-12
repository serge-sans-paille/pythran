//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_GENERIC_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_GENERIC_SPLIT_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/swar/functions/split_multiplies.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_multiplies_
                                      , tag::cpu_
                                      , (A0)(A1)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((generic_< arithmetic_<A0> >))
                                        ((generic_< arithmetic_<A0> >))
                                        ((generic_< arithmetic_<A1> >))
                                      )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1, A1 & a3) const
    {
      result_type a2;
      boost::simd::split_multiplies(a0, a1, a2, a3);
      return a2;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_multiplies_, tag::cpu_
                                      , (A0)
                                      , ( simd::meta::is_upgradable<A0> )
                                      , (generic_< arithmetic_<A0> >)
                                        (generic_< arithmetic_<A0> >)
                                      )
  {
    typedef typename dispatch::meta::upgrade<A0>::type part;
    typedef std::pair<part,part>                       result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      part first, second;
      boost::simd::split_multiplies( a0, a1, first, second );
      return result_type(first, second);
    }
  };
} } }

#endif
