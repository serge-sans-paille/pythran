//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_DAWSON_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_DAWSON_HPP_INCLUDED
#include <nt2/euler/functions/dawson.hpp>
#include <nt2/euler/functions/details/dawson_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dawson_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x = nt2::abs(a0);
      A0 xx = nt2::sqr(x);
      if( x < static_cast<A0>(3.25) )
      {
        return a0*details::dawson_kernel<A0>::dawson1(xx);
      }
      xx = rec(xx);
      if( x < static_cast<A0>(6.25) )
      {
        A0 y = details::dawson_kernel<A0>::dawson2(xx, x);
        return nt2::copysign( nt2::Half<A0>()*y, a0);
      }
      if( x > static_cast<A0>(1.0e9) )
        return  nt2::Half<A0>()* nt2::copysign(rec(x), a0);
      /* 6.25 to 1.0e9 */
      A0 y = details::dawson_kernel<A0>::dawson3(xx, x);
      return nt2::copysign( nt2::Half<A0>()*y, a0);
    }
  };

} }


#endif
