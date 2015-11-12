//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_COMMON_ZERO_CROSSING_RATE_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_COMMON_ZERO_CROSSING_RATE_HPP_INCLUDED

#include <nt2/signal/functions/zero_crossing_rate.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::zero_crossing_rate_, tag::cpu_,
                              (A0),
                              (scalar_<floating_<A0 > >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& ) const
    {
      return nt2::Zero<result_type>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::zero_crossing_rate_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<floating_<A0> > )
                              (scalar_<integer_<A1> > )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& ) const
    {
      return nt2::Zero<result_type>();
    }
  };
} }

#endif
