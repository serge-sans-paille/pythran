//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_FAST_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_FAST_HYPOT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fast_hypot.hpp>
#include <boost/simd/include/functions/simd/sqrt.hpp>
#include <boost/simd/include/functions/simd/sqr.hpp>
#include <boost/simd/include/functions/simd/fma.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_hypot_, tag::cpu_
                                    , (A0)
                                    , (generic_< floating_<A0> >)
                                      (generic_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::sqrt(boost::simd::fma(a0, a0, sqr(a1)));
    }
  };

} } }

#endif
