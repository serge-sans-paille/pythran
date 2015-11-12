//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVCEIL_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divceil.hpp>
#include <boost/simd/include/functions/scalar/ceil.hpp>
#include <boost/simd/include/functions/scalar/iceil.hpp>
#include <boost/simd/include/functions/scalar/divs.hpp>
#include <boost/simd/include/functions/scalar/inc.hpp>
#include <boost/simd/include/functions/scalar/oneplus.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divceil_, tag::cpu_
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
        result_type q = a0/a1;
        result_type r =a0-q*a1;
        if ((r != Zero<result_type>())&&((a0^a1) >= 0)) return oneplus(q);
        return q;
      }
      else
        return ((a0>0) ? Valmax<result_type>() : Valmin<result_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divceil_, tag::cpu_
                                    , (A0)
                                    , (scalar_< signed_<A0> >)
                                      (scalar_< signed_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
        return static_cast<result_type>(iceil(static_cast<double>(a0)/static_cast<double>(a1)));
      else
        return (a0) ? ((a0>0) ? Valmax<result_type>() : Valmin<result_type>()) : Zero<result_type>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divceil_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unsigned_<A0> >)
                                      (scalar_< unsigned_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
      {
        result_type q = a0/a1;
        if (a0-q*a1 != Zero<result_type>()) return inc(q);
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

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divceil_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return ceil(a0/a1); }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
