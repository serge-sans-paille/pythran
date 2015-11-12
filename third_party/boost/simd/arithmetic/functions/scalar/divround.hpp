//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVROUND_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVROUND_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divround.hpp>
#include <boost/simd/include/functions/scalar/round.hpp>
#include <boost/simd/include/functions/scalar/copysign.hpp>
#include <boost/simd/include/functions/scalar/is_odd.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround_, tag::cpu_
                                    , (A0)
                                    , (scalar_< int64_<A0> >)
                                      (scalar_< int64_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (!a0) return  Zero<result_type>();
      if(a1)
      {
        A0 aa0 = abs(a0);
        A0 aa1 = abs(a1);
        result_type q = aa0/aa1;
        result_type r = aa0-q*aa1;
        if ((r!= 0) && (r-is_odd(aa1) >= (aa1 >> 1))) ++q;
        return copysign(q, a0*a1);
      }
      else
        return ((a0>0) ? Valmax<result_type>() : Valmin<result_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround_, tag::cpu_
                                    , (A0)
                                    , (scalar_< signed_<A0> >)
                                      (scalar_< signed_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
        return static_cast<result_type >(round(static_cast<double>(a0)/static_cast<double>(a1)));
      else
      {
        return (a0) ? ((a0>0) ? Valmax<result_type>() : Valmin<result_type>()) : Zero<result_type>();
      }
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unsigned_<A0> >)
                                      (scalar_< unsigned_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
      {
        result_type q = a0/a1;
        result_type r = a0-q*a1;
        if ((r!= 0) && (r-is_odd(a1) >= (a1 >> 1))) ++q;
        return q;
      }
      else
        return (a0) ? Valmax<result_type>() : Zero<result_type>();
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::round(a0/a1);
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
