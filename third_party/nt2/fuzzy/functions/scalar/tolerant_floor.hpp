//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SCALAR_TOLERANT_FLOOR_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SCALAR_TOLERANT_FLOOR_HPP_INCLUDED
#include <nt2/fuzzy/functions/tolerant_floor.hpp>
#include <nt2/include/constants/threeeps.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/min.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/negif.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tolerant_floor_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0& a0)
    {
        // Hagerty's FL5 function
        const result_type ct = Threeeps<result_type>();
        const result_type q = (a0<Zero<result_type>())? One<result_type>()-ct : One<result_type>();
        const result_type rmax = q/(Two<result_type>()-ct);
        result_type t1 = One<result_type>()+nt2::floor(a0);
        t1 = (ct/q)*(t1 < Zero<result_type>()? -t1: t1);
        t1 = nt2::floor(a0+nt2::max(ct,nt2::min(rmax,t1)));
        return ((a0<=Zero<result_type>()||(t1-a0)<rmax)) ? t1 : nt2::minusone(t1);
    }
  };
} }


#endif
