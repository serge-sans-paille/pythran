//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_MINUSONE_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_MINUSONE_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/minusone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/functions/simd/selsub.hpp>
#include <boost/simd/include/functions/simd/is_not_equal.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minusone_, tag::cpu_
                                    , (A0)
                                    , (generic_<arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return selsub(neq(a0, Valmin<result_type>()), a0, One<result_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::minusone_, tag::cpu_
                                    , (A0)
                                    , (generic_<floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return a0-One<result_type>();
    }
  };

} } }
#endif
