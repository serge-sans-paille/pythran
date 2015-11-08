//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MINMOD_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MINMOD_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/minmod.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/is_gez.hpp>
#include <boost/simd/include/functions/simd/is_nltz.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::minmod_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<int_<A0>,X>))((simd_<int_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return if_else_zero(is_gez(b_xor(a0, a1)),boost::simd::min(a0, a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::minmod_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<uint_<A0>,X>))((simd_<uint_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return  boost::simd::min(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::minmod_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return if_else_zero(is_nltz((a0*a1)),boost::simd::min(a0, a1));
    }
  };
} } }


#endif
