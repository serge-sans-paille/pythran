//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_HMSB_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_HMSB_HPP_INCLUDED

#include <boost/simd/reduction/functions/hmsb.hpp>
#include <boost/simd/include/functions/simd/bits.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <climits>
#include <cstddef>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef std::size_t result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;

      result_type z = 0;
      const result_type N = meta::cardinal_of<A0>::value;
      for(result_type i = 0; i != N; ++i)
      {
        z |= (bits(a0[i]) >> (sizeof(stype)*CHAR_BIT - 1)) << i;
      }
      return z;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<logical_<A0>,X>))
                                    )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::hmsb(boost::simd::genmask(a0));
    }
  };
} } }

#endif
