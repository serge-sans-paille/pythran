//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_SQRT1PM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_SQRT1PM1_HPP_INCLUDED
#include <nt2/exponential/functions/sqrt1pm1.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt1pm1_, tag::cpu_
                            , (A0)
                            , ((generic_<complex_< floating_<A0 > > >))
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      result_type tmp = nt2::sqrt(oneplus(a0));
      return if_else(lt(nt2::abs(a0), Half<rtype>()),
                     nt2::divides(a0, oneplus(tmp)),
                     minusone(tmp));
    }
  };
} }


#endif
