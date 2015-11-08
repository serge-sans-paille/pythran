//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_POSMAX_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_POSMAX_HPP_INCLUDED

#include <nt2/reduction/functions/posmax.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posmax_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef std::size_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      typedef typename meta::as_logical<rtype>::type ltype;

      rtype const absa0 = nt2::abs(a0);
      result_type tmp   = posmax(absa0);
      ltype const test  = eq(absa0, absa0[tmp]);

      if(nt2::inbtrue(test) > 1)
      {
        return nt2::posmax(nt2::if_else(test, nt2::arg(a0), Minf<rtype>()));
      }

      return tmp;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::posmax_, tag::cpu_, (A0)
                              , (generic_< dry_< arithmetic_<A0> > >)
    )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::posmax(nt2::abs(a0));
    }
  };
} }

#endif
