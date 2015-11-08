//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVFLOOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVFLOOR_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divfloor.hpp>
#include <boost/simd/include/functions/scalar/divs.hpp>
#include <boost/simd/include/functions/scalar/iceil.hpp>
#include <boost/simd/include/functions/scalar/floor.hpp>
#include <boost/simd/include/functions/scalar/minusone.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divfloor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< int64_<A0> >)
                                      (scalar_< int64_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (!a0) return  Zero<result_type>();
      if(a1)
      {
        result_type q = divs(a0, a1);
        result_type r = a0-q*a1;
        if ((r != Zero<result_type>())&&((a0^a1) <= 0)) return minusone(q);
        return q;
      }
      else
        return ((a0>0) ? Valmax<result_type>() : Valmin<result_type>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divfloor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< signed_<A0> >)
                                      (scalar_< signed_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
        return static_cast<result_type >(-iceil(-static_cast<double>(a0)/static_cast<double>(a1)));
      else
      {
        return (a0) ? ((a0>0) ? Valmax<result_type>() : Valmin<result_type>()) : Zero<result_type>();
      }
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divfloor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unsigned_<A0> >)
                                      (scalar_< unsigned_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if(a1)
        return divs(a0, a1);
      else
        return (a0) ? Valmax<result_type>() : Zero<result_type>();
    }
  };

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divfloor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                    )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::floor(a0/a1);
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
