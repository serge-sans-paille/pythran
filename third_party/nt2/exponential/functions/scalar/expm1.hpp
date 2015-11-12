//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXPM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXPM1_HPP_INCLUDED
#include <nt2/exponential/functions/expm1.hpp>
#include <nt2/exponential/functions/details/expm1_kernel.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/logeps.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/functions/scalar/expm1.hpp>
#include <nt2/include/functions/scalar/is_greater.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , (scalar_<floating_<A0> >)
                            )
  {
     typedef A0 result_type;
     NT2_FUNCTOR_CALL(1)
     {
       if(lt(a0, Logeps<A0>())) return Mone<A0>();
       if(gt(a0, Maxlog<A0>())) return  Inf<A0>();
       return details::expm1_kernel<A0>::expm1(a0);
     }
  };
} }

#endif
