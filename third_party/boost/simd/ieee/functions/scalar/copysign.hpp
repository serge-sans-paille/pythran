//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_COPYSIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_COPYSIGN_HPP_INCLUDED

#include <boost/simd/ieee/functions/copysign.hpp>
#include <boost/simd/include/functions/scalar/abss.hpp>
#include <boost/simd/include/functions/scalar/signnz.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::copysign_, tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::abss(a0)*boost::simd::signnz(a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::copysign_, tag::cpu_
                                    , (A0)
                                    , (scalar_< double_<A0> >)
                                      (scalar_< double_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
    #ifdef BOOST_SIMD_HAS_COPYSIGN
      return ::copysign(a0, a1);
    // _copysign appears to be bogus for a1 = -0 in old MSVCRT
    #elif defined(BOOST_SIMD_HAS__COPYSIGN) && !defined(__MSVCRT__)
      return ::_copysign(a0, a1);
    #else
      return boost::math::copysign(a0, a1);
    #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::copysign_, tag::cpu_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                      (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
    #ifdef BOOST_SIMD_HAS_COPYSIGNF
      return ::copysignf(a0, a1);
    #elif defined(BOOST_SIMD_HAS__COPYSIGNF)
      return ::_copysignf(a0, a1);
    #else
        return boost::math::copysign(a0, a1);
    #endif
    }
  };
} } }

#endif
