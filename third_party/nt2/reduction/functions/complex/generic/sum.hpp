//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_SUM_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_SUM_HPP_INCLUDED

#include <nt2/reduction/functions/sum.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/shuffle.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sum_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::scalar_of<A0>::type  result_type;
    typedef typename meta::as_real<A0>::type    r_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(sum(bitwise_cast<r_t>(a0)));
    }
  };
} }

#endif
