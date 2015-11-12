//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_MINNUMMAG_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_MINNUMMAG_HPP_INCLUDED

#include <nt2/ieee/functions/minnummag.hpp>
#include <nt2/include/functions/minmag.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::minnummag_, tag::cpu_,
                              (A0),
                              (generic_<complex_<floating_<A0> > >)
                              (generic_<complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type lA0;
      const lA0 cond = is_nan(a0);
      const A0 a = if_else(cond, a0, a1);
      const A0 b = if_else(cond, a1, a0);
      return minmag(a, b);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::minnummag_, tag::cpu_,
                              (A0),
                              (generic_<dry_<floating_<A0> > >)
                              (generic_<dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_cast<A0>(minnummag(real(a0), real(a1)));
    }
  };
} }


#endif
