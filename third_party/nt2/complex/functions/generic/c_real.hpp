//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMPLEX_FUNCTIONS_GENERIC_C_REAL_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_GENERIC_C_REAL_HPP_INCLUDED

#include <nt2/complex/functions/c_real.hpp>
#include <nt2/complex/functions/real.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::c_real_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(real(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::c_real_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::c_real_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > > )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };

} }

#endif
