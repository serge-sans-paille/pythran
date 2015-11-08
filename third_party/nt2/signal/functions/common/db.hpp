//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_COMMON_DB_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_COMMON_DB_HPP_INCLUDED

#include <nt2/signal/functions/db.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/mag2db.hpp>
#include <nt2/include/functions/pow2db.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp10.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/ten.hpp>

namespace nt2 { namespace ext
{
  // voltage is the default
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::mag2db(a0);
    }
  };

  //normalized only for voltage
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return nt2::mag2db(a0,a1);
    }
  };

  // value + type of db
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (target_< unspecified_<A1> >)
                            )
  {

    typedef A0 result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& e, const details::voltage_t&) const
    {
      return nt2::mag2db(e);
    }

    BOOST_FORCEINLINE result_type
    operator()(const A0& e, const details::power_t&) const
    {
      return nt2::pow2db(e);
    }
  };

  // value & ref. + type of db
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::db_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (target_< unspecified_<A1> >)
                              (generic_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type
    operator()(const A0& e, const details::voltage_t&, const A0& n) const
    {
      return nt2::mag2db(e,n);
    }
    };
} }

#endif
