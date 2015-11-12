//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SLICE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SLICE_HPP_INCLUDED

#include <boost/simd/swar/functions/slice.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::slice_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , ( boost::mpl::bool_
                                          <
                                            A1::static_size == A0::static_size/2
                                          >
                                        )
                                      , ((simd_<unspecified_<A0>,X>))
                                        ((simd_<unspecified_<A1>,Y>))
                                        ((simd_<unspecified_<A1>,Y>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& a1, A1& a2) const
    {
      for(size_t i=0; i!=A1::static_size; ++i)
      {
        a1[i] = a0[i];
        a2[i] = a0[i+A1::static_size];
      }
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::slice_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , ( boost::mpl::and_
                                          < boost::mpl::bool_
                                            <
                                              A1::static_size == A0::static_size/2
                                            >
                                          , mpl::equal_to < mpl::sizeof_<A0>
                                                          , mpl::sizeof_<typename A0::type>
                                                          >
                                          , mpl::equal_to < mpl::sizeof_<A1>
                                                          , mpl::sizeof_<typename A1::type>
                                                          >
                                          >
                                        )
                                      , ((simd_<logical_<A0>,X>))
                                        ((simd_<logical_<A1>,Y>))
                                        ((simd_<logical_<A1>,Y>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& a1, A1& a2) const
    {
      typedef typename A0::type type0;
      typedef typename A1::type type1;

      type1 l1,l2;
      boost::simd::slice(bitwise_cast<type0>(a0),l1,l2);

      a1 = bitwise_cast<A1>(l1);
      a2 = bitwise_cast<A1>(l2);
    }
  };
} } }

#endif
