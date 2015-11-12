//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPM1_HPP_INCLUDED

#include <nt2/exponential/functions/expm1.hpp>
#include <nt2/exponential/functions/details/expm1_kernel.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/logeps.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace details
//why do I need that ?! its already in nt2/exponential/functions/details/expm1_kernel.hpp
{
  template < class A0, class sA0>
  struct expm1_kernel;
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
     typedef A0 result_type;
     NT2_FUNCTOR_CALL(1)
     {
       typedef typename meta::scalar_of<A0>::type sA0;
       typedef nt2::details::expm1_kernel<A0, sA0> kernel_t;
       return if_else(lt(a0, Logeps<A0>()),
                      Mone<A0>(),
                      if_else(gt(a0, Maxlog<A0>()),
                              Inf<A0>(),
                              kernel_t::expm1(a0)
                             )
                  );
     }
  };
} }

#endif
