//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMPLEX_FUNCTIONS_GENERIC_PROJ_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_GENERIC_PROJ_HPP_INCLUDED

#include <nt2/complex/functions/proj.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proj_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::if_else(nt2::is_inf(a0), nt2::Inf<result_type>(), a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proj_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return if_else(is_inf(a0), nt2::Inf<result_type>(), a0);
    }
  };


} }
#endif
