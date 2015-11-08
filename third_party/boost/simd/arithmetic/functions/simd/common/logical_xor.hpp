//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_LOGICAL_XOR_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/logical_xor.hpp>
#include <boost/simd/include/functions/simd/mask2logical.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::logical_xor_, tag::cpu_, (A0)(A1)(X)
                                    , ((simd_<fundamental_<A0>,X>))
                                      ((simd_<fundamental_<A1>,X>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
     return mask2logical(b_xor(genmask(a0), genmask(a1)));
    }
  };
} } }

#endif
