//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SPLATTED_SUM_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SPLATTED_SUM_HPP_INCLUDED

#include <nt2/swar/functions/splatted_sum.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/shuffle.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::splatted_sum_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<dry_<arithmetic_<A0> >,X>))
                            )
  {
    typedef A0                                result_type;
    typedef typename meta::as_real<A0>::type  r_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(splatted_sum(bitwise_cast<r_t>(a0)));
    }
  };
} }

#endif
