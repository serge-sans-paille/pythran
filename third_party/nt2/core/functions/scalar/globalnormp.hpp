//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_GLOBALNORMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_GLOBALNORMP_HPP_INCLUDED

#include <nt2/core/functions/globalnormp.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/include/functions/abs.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalnormp_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef typename  meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const &) const
    {
      return nt2::abs(a);
    }
  };
} }

#endif
