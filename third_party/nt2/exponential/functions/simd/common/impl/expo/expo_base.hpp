//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED

#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/exponential/functions/scalar/impl/expo/f_expo_reduction.hpp>
#include <nt2/exponential/functions/scalar/impl/expo/d_expo_reduction.hpp>
#include <nt2/exponential/functions/scalar/impl/expo/expo_scale.hpp>
#include <boost/simd/sdk/config.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#endif

namespace nt2 { namespace details
{
  template < class A0, class Tag,  class Speed_Tag >
  struct exponential < A0, Tag, tag::simd_type, Speed_Tag, double>
  {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    // compute exp(ax)
    static inline A0 expa(const A0& a0)
    {
      A0 hi, lo, x;
      A0 k = reduc_t::reduce(a0, hi, lo, x);
      A0 c = reduc_t::approx(x);
      c = reduc_t::finalize(x, c, hi, lo);
      c = nt2::if_zero_else(reduc_t::isleminlog(a0), scale(c, k));
      c = nt2::if_else(reduc_t::isgemaxlog(a0), nt2::Inf<A0>(), c);
      #ifdef BOOST_SIMD_NO_INVALIDS
        return c;
      #else
       return if_nan_else(is_nan(a0), c);
      #endif
    }
  };

  template < class A0, class Tag,  class Speed_Tag >
  struct exponential < A0, Tag, tag::simd_type, Speed_Tag, float>
  {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    // compute exp(ax)
    static inline A0 expa(const A0& a0)
    {
      A0 x;
      A0 k = reduc_t::reduce(a0, x);
      x = reduc_t::approx(x);
      x = nt2::if_zero_else(reduc_t::isleminlog(a0), scale(x, k));
      x = nt2::if_else(reduc_t::isgemaxlog(a0), nt2::Inf<A0>(), x);
      #ifdef BOOST_SIMD_NO_INVALIDS
        return x;
      #else
        return if_nan_else(is_nan(a0), x);
      #endif
    }
  };

} }

#endif
