//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_TWOPOWER_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_TWOPOWER_HPP_INCLUDED
#include <boost/simd/bitwise/functions/twopower.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/functions/scalar/is_ltz.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::twopower_, tag::cpu_, (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return (is_ltz(a0))?Zero<A0>():(One<A0>()<<a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::twopower_, tag::cpu_, (A0)
                            , (scalar_< unsigned_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return One<A0>()<<a0; }
  };
} } }

#endif
