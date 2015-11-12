//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOGSPACE_ADD_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_LOGSPACE_ADD_HPP_INCLUDED
#include <nt2/exponential/functions/logspace_add.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/max.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_add_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 tmp = -nt2::abs(a0-a1);
      A0 r = nt2::max(a0,a1)+nt2::log1p(nt2::exp(tmp));
      #ifndef BOOST_SIMD_NO_NANS
      return is_nan(tmp) ? a0+a1 : r;
      #else
      return r;
      #endif
    }
  };
} }

#endif
