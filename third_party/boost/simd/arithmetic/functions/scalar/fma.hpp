//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FMA_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fma.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fma_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      return a0*a1+a2;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fma_, tag::cpu_
                                    , (A0)
                                    , (scalar_< double_<A0> >)
                                      (scalar_< double_<A0> >)
                                      (scalar_< double_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      //TO DO find a correct fma policy
      //      fma is incorrect this is Bugzilla Bug 3268 for glibc
      return a0*a1+a2;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fma_, tag::cpu_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                      (scalar_< single_<A0> >)
                                      (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      //TO DO find a correct fma policy
      return a0*a1+a2;
      //         return ::fma(a0, a1, a2);
    }
  };
} } }


#endif
