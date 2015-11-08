//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SPLIT_HPP_INCLUDED

#include <nt2/swar/functions/split.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::split_, tag::cpu_,
                              (A0)(A1)(X),
                              ((simd_<complex_<arithmetic_<A0> >,X>))
                              ((simd_<complex_<arithmetic_<A1> >,X>))
                              ((simd_<complex_<arithmetic_<A1> >,X>))
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A1 & a1, A1 & a2) const
    {
      typedef typename meta::as_real<A1>::type rA1;
      rA1 ar0, ar1, ai0, ai1;
      split(nt2::real(a0), ar0, ar1);
      split(nt2::imag(a0), ai0, ai1);
      a1 = A1(ar0, ai0);
      a2 = A1(ar1, ai1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::split_, tag::cpu_,
                              (A0)(A1)(X),
                              ((simd_<dry_<arithmetic_<A0> >,X>))
                              ((simd_<dry_<arithmetic_<A1> >,X>))
                              ((simd_<dry_<arithmetic_<A1> >,X>))
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A1 & a1, A1 & a2) const
    {
      typedef typename meta::as_real<A1>::type rA1;
      rA1 ai0, ai1;
      split(nt2::imag(a0), ai0, ai1);
      a1 = bitwise_cast<A1>(ai0);
      a2 = bitwise_cast<A1>(ai1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::split_, tag::cpu_,
                              (A0)(X),
                              ((simd_<complex_<arithmetic_<A0> >,X>))
                            )
  {
    typedef typename boost::dispatch::meta::upgrade<typename A0::value_type>::type base_t;
    typedef typename boost::simd::meta::vector_of< base_t
                                                 , A0::static_size
                                                 >::type result_type;
    inline result_type operator()(A0 const& a0) const
    {
      return result_type(split(nt2::real(a0)), split(nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::split_, tag::cpu_,
                              (A0)(X),
                              ((simd_<dry_<arithmetic_<A0> >,X>))
                            )
  {
    typedef typename boost::dispatch::meta::upgrade<typename A0::value_type>::type base_t;
    typedef typename boost::simd::meta::vector_of< base_t
                                                 , A0::static_size
                                                 >::type result_type;
    inline result_type operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(split(nt2::real(a0)));
    }
  };

} }

#endif
