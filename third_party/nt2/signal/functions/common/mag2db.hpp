//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_COMMON_MAG2DB_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_COMMON_MAG2DB_HPP_INCLUDED

#include <nt2/signal/functions/mag2db.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/log10.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/constants/ten.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mag2db_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return nt2::Ten<result_type>()*nt2::log10(nt2::sqr(a0)/a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mag2db_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::Ten<result_type>()*nt2::log10(nt2::sqr(a0));
    }
  };
} }

#endif
