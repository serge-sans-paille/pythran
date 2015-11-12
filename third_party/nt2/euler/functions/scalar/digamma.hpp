//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_DIGAMMA_HPP_INCLUDED

#include <nt2/euler/functions/digamma.hpp>
#include <nt2/euler/functions/details/digamma_kernel.hpp>
#include <nt2/include/constants/digammalargelim.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/tanpi.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::digamma_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 result = nt2::Zero<A0>();
      A0 x = a0;
      if (a0 == 0) return copysign(Inf<A0>(), a0);
      if( x < 0)
      {
        if ( 0 && (x > -1))
          result = -x;
        else
        {
          x =  nt2::oneminus(x);
          result = x - nt2::floor(x);
        }
        if (result > 0.5)  result -= 1;
        if (result == 0.5)
          result =  Zero<A0>();
        else if (result)
          result = nt2::Pi<A0>()/nt2::tanpi(result);
        else
          result = Nan<A0>();
        // we are ready to increment result that was
        // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
        // Nan<A0>                   if a0 < 0  and remainder == 0
        // 0                         in any other cases
      }
      if(x >= Digammalargelim<A0>())
      { // If we're above the lower-limit for the asymptotic expansion then use it:
        return details::digamma_kernel<A0>::digamma_imp_large(x)+result;
      }
      // If x > 2 reduce to the interval [1,2]:
      while(x > 2)
      {
        x      -= 1;
        result += 1/x;
      }
      // If x < 1 use shift to > 1:
      if(x < 1)
      {
        result = -1/x;
        x      += 1;
      }
      return details::digamma_kernel<A0>::digamma_1_2(x)+result;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::digamma_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::digamma(double(a0));
    }
  };

} }

#endif
