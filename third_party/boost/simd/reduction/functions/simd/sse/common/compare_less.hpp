//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_COMMON_COMPARE_LESS_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_COMMON_COMPARE_LESS_HPP_INCLUDED
#ifdef BOOST_SIMD_SSE_FAMILY

#include <boost/simd/reduction/functions/compare_less.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/reverse.hpp>
#include <boost/simd/include/functions/simd/hmsb.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::compare_less_
                                    , boost::simd::tag::sse2_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type  sA0;
    typedef typename meta::as_logical<sA0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      A0            const  r0 = reverse(a0)   ,  r1 = reverse(a1);
      unsigned int  const mlt = hmsb(r0 < r1) , mgt = hmsb(r0 > r1);

      return result_type( (mlt > mgt) && mlt );
    }
  };
} } }

#endif
#endif
