//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_SIGN_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_SIGN_HPP_INCLUDED

#include <nt2/ieee/functions/sign.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/simd/max.hpp>
#include <nt2/include/functions/simd/is_finite.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/ldexp.hpp>
#include <nt2/include/functions/simd/exponent.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/simd/hypot.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sign_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type real_t;
      typedef typename meta::as_logical<real_t>::type logi_t;
      typedef typename meta::as_integer<real_t>::type int_t;
      real_t r = nt2::real(a0);
      real_t i = nt2::imag(a0);
      int_t  e = -nt2::max(nt2::exponent(r), nt2::exponent(i));
      r = nt2::ldexp(r,e);
      i = nt2::ldexp(i,e);
      real_t mod = nt2::hypot(r, i);
      result_type z = result_type(r, i)/mod;
#ifndef BOOST_SIMD_NO_NANS
       logi_t isinv = nt2::is_invalid(a0);
       if(nt2::any(isinv))
       {
         real_t si =  nt2::sign(i);
         real_t sr =  nt2::sign(r);
         z = nt2::if_else(isinv,
                          nt2::if_else(nt2::logical_andnot(nt2::is_finite(i),nt2::is_nan(r)),
                                       result_type(sr),
                                       nt2::if_else(nt2::logical_andnot(nt2::is_finite(r),nt2::is_nan(i)),
                                                    mul_i(si),
                                                    z
                                                   )
                                      ),
                          z
                         );
       }
       z =  nt2::if_else(nt2::is_real(a0),
                         result_type(nt2::real(z)),
                         nt2::if_else(nt2::is_imag(a0), mul_i(nt2::imag(z)), z)
                        );
#endif
       return nt2::if_else(nt2::is_eqz(mod), a0, z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sign_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::sign(nt2::real(a0)));
    }
  };

} }

#endif
