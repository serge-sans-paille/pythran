//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMPLEX_CONSTANTS_GENERIC_CNAN_HPP_INCLUDED
#define NT2_COMPLEX_CONSTANTS_GENERIC_CNAN_HPP_INCLUDED

#include <nt2/complex/constants/cnan.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::Cnan, tag::cpu_, (A0)
                             , ((target_< generic_< complex_< arithmetic_<A0> > > >))
                             )
  {
    typedef typename A0::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      typedef typename meta::as_real<result_type>::type real_t;
      return result_type(Nan<real_t>(), Nan<real_t>());
    }
  };
} }

#endif
