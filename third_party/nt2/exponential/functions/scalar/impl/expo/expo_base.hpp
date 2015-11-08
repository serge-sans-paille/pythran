//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED

#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/exponential/functions/scalar/impl/selection_tags.hpp>
#include <nt2/exponential/functions/scalar/impl/expo/f_expo_reduction.hpp>
#include <nt2/exponential/functions/scalar/impl/expo/d_expo_reduction.hpp>
#include <nt2/exponential/functions/scalar/impl/expo/expo_scale.hpp>
#include <boost/simd/sdk/config.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

namespace nt2 { namespace details
{
  template < class A0,
             class Tag,
             class Style ,
             class Speed_Tag = fast_tag,
             class base_A0 = typename meta::scalar_of<A0>::type>
  struct exponential{};


  template < class A0, class Tag,  class Speed_Tag>
  struct exponential< A0, Tag, tag::not_simd_type, Speed_Tag, double>
  {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    // compute exp(ax) where a is 1, 2 or ten depending on Tag
    static inline A0 expa(const A0& a0)
    {
      if (reduc_t::isgemaxlog(a0)) return Inf<A0>();
      if (reduc_t::isleminlog(a0)) return Zero<A0>();
      #ifndef BOOST_SIMD_NO_INVALIDS
        if (is_nan(a0)) return a0;
      #endif
      A0 hi, lo, x;
      A0 k = reduc_t::reduce(a0, hi, lo, x);
      A0 c = reduc_t::approx(x);
      c = reduc_t::finalize(x, c, hi, lo);
      return  scale(c, k);
    }
  };

  template < class A0, class Tag,  class Speed_Tag>
  struct exponential< A0, Tag, tag::not_simd_type, Speed_Tag, float>
  {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    // compute exp(ax) where a is 1, 2 or ten depending on Tag
    static inline A0 expa(const A0& a0)
    {
      if (reduc_t::isgemaxlog(a0)) return Inf<A0>();
      if (reduc_t::isleminlog(a0)) return Zero<A0>();
      #ifndef BOOST_SIMD_NO_INVALIDS
        if (is_nan(a0)) return a0;
      #endif
      A0 x;
      A0 k = reduc_t::reduce(a0, x);
      x = reduc_t::approx(x);
      return scale(x, k);
    }
  };
} }


#endif
