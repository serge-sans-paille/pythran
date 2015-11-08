//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_WMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_WMEAN_HPP_INCLUDED

#include <nt2/core/functions/wmean.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::wmean_, tag::cpu_, (A0)(A1)
                              , (scalar_< unspecified_<A0> >)
                              (scalar_< floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const &) const
    {
      return a;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::wmean_, tag::cpu_, (A0)(A1)(A2)
                              , (scalar_< unspecified_<A0> >)
                              (scalar_< floating_<A1> >)
                              (scalar_< integer_<A2> > )
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const &, A2 const &) const
    {
      return a;
    }
  };
} }

#endif
