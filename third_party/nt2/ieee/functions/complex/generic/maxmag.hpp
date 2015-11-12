//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_MAXMAG_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_MAXMAG_HPP_INCLUDED
#include <nt2/ieee/functions/maxmag.hpp>
#include <nt2/include/functions/maxmag.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/real.hpp>



namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maxmag_, tag::cpu_,
                                     (A0),
                                     (generic_<complex_<floating_<A0> > >)
                                     (generic_<complex_<floating_<A0> > >)
                                   )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type rA0;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::max(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maxmag_, tag::cpu_,
                                     (A0),
                                     (generic_<dry_<floating_<A0> > >)
                                     (generic_<dry_<floating_<A0> > >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      rtype absa0 = nt2::abs(a0);
      rtype absa1 = nt2::abs(a1);
      result_type r = if_else(gt(absa0, absa1), a0, a1);
      return if_else(eq(absa0, absa1), if_else(is_gtz(a0), a0, a1), r);
    }

  };
} }


#endif
