//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_SCALAR_DOT_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_SCALAR_DOT_HPP_INCLUDED

#include <nt2/reduction/functions/dot.hpp>
#include <nt2/include/functions/scalar/conj.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                              (scalar_< integer_<A1> > )
                            )
  {
    typedef typename  meta::as_floating<A0>::type f_t;
    typedef typename  meta::as_real<f_t>::type    result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a, A0 const& b, A1 const &) const
    {
      return a*nt2::conj(b);
    }
  };
} }

#endif
