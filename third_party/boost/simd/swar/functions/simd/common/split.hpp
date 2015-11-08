//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED

#include <boost/simd/swar/functions/split.hpp>
#include <boost/simd/include/functions/simd/split_low.hpp>
#include <boost/simd/include/functions/simd/split_high.hpp>
#include <boost/simd/include/functions/simd/combine.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                      )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& a1, A1& a2) const
    {
      a1 = split_low(a0);
      a2 = split_high(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::split_
                                   , tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<arithmetic_<A0>, X>))
                                   )
  {
    typedef typename dispatch::meta::upgrade<typename A0::value_type>::type base_t;
    typedef typename simd::meta::vector_of< base_t
                                          , A0::static_size
                                          >::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return eval(a0, simd::meta::is_upgradable<A0>());
    }

    BOOST_FORCEINLINE result_type eval2(A0 const& a0, boost::mpl::true_) const
    {
      typename simd::meta::vector_of< base_t
                                    , A0::static_size/2
                                    >::type a00,a01;
      split(a0, a00, a01);
      return boost::simd::combine(a00,a01);
    }

    BOOST_FORCEINLINE result_type eval2(A0 const& a0, boost::mpl::false_) const
    {
      return make<result_type>( static_cast<base_t>( extract<0>(a0) )
                              , static_cast<base_t>( extract<1>(a0) )
                              );
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, boost::mpl::false_) const
    {
      return a0;
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, boost::mpl::true_) const
    {
      return eval2(a0, boost::mpl::bool_<(A0::static_size>=4)>());
    }
  };
} } }

#endif
