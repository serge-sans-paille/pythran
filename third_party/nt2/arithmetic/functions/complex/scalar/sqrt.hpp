//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_SCALAR_SQRT_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_SCALAR_SQRT_HPP_INCLUDED

#include <nt2/arithmetic/functions/sqrt.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
//#include <cmath>

namespace nt2 { namespace ext
{
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt_, tag::cpu_, (A0)
//                             , (scalar_< complex_< arithmetic_<A0> > >)
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       return std::sqrt(a0); //erroneous in 4.6 for inf*i
//     }
//   };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt_, tag::cpu_, (A0)
                            , (scalar_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_complex<rA0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const rA0 root = nt2::sqrt(nt2::abs(nt2::real(a0)));
      return if_else(is_ltz(a0),
                     result_type(Zero<rA0>(), root),
                     result_type(root, Zero<rA0>()));
    }
  };

} }

#endif
