//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_RSHL_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_RSHL_HPP_INCLUDED

#include <boost/simd/bitwise/functions/rshl.hpp>
#include <boost/simd/include/functions/scalar/unary_minus.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/functions/scalar/shr.hpp>
#include <boost/simd/include/functions/scalar/shift_left.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rshl_, tag::cpu_ , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return (a1>0) ? shl(a0, a1) : shr(a0, boost::simd::neg(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rshl_, tag::cpu_ , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< unsigned_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return shl(a0, a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rshl_, tag::cpu_ , (A0)(A1)
                            , (scalar_< floating_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type itype;
      return bitwise_cast<result_type>(rshl(bitwise_cast<itype>(a0),a1));
    }
  };
} } }

#endif
