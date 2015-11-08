//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_GENERIC_SLICE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_GENERIC_SLICE_HPP_INCLUDED

#include <boost/simd/swar/functions/slice.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slice_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , ((generic_< unspecified_<A0> >))
                                      ((generic_< unspecified_<A1> >))
                                    )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 & a2) const
    {
      result_type a1;
      boost::simd::slice(a0, a1, a2);
      return a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slice_, tag::cpu_
                                    , (A0)
                                    , (generic_< unspecified_<A0> >)
                                    )
  {
    typedef typename  meta::vector_of < typename A0::value_type
                                      , A0::static_size / 2
                                      >::type                     part;
    typedef std::pair<part,part>                                  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      part first, second;
      boost::simd::slice( a0, first, second );
      return result_type(first, second);
    }
  };
} } }

#endif
