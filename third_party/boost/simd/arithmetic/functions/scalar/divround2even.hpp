//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVROUND2EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVROUND2EVEN_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divround2even.hpp>
#include <boost/simd/include/functions/scalar/round2even.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/is_even.hpp>
#include <boost/simd/include/functions/scalar/is_odd.hpp>
#include <boost/simd/include/functions/scalar/copysign.hpp>
#include <boost/simd/include/functions/scalar/tofloat.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround2even_, tag::cpu_
                                    , (A0)
                                    , (scalar_< int64_<A0> >)
                                      (scalar_< int64_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename boost::dispatch::meta::as_integer<A0, unsigned>::type uitype;
      if (!a0) return  Zero<result_type>();
      if(a1)
      {
        uitype aa0 = abs(a0);
        uitype aa1 = abs(a1);
        uitype q = aa0/aa1;
        uitype rx2 = 2*(aa0-q*aa1);
        if (rx2 >= aa1)
        {
          if ((rx2 == aa1) && is_even(q)) --q;
          ++q;
        }
        return copysign(result_type(q), a0*a1);
      }
      else
        return ((a0>0) ? Valmax<result_type>() : Valmin<result_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround2even_, tag::cpu_
                                    , (A0)
                                    , (scalar_< signed_<A0> >)
                                      (scalar_< signed_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
        return static_cast<result_type >(round2even(static_cast<double>(a0)/static_cast<double>(a1)));
      else
      {
        return (a0) ? ((a0>0) ? Valmax<result_type>() : Valmin<result_type>()) : Zero<result_type>();
      }
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround2even_, tag::cpu_
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
        result_type rx2 = 2*(a0-q*a1);
        if (rx2 >= a1)
        {
          if ((rx2 == a1) && is_even(q)) --q;
          ++q;
        }
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

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divround2even_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> > )
                                      (scalar_< floating_<A0> > )
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return round2even(a0/a1);
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
