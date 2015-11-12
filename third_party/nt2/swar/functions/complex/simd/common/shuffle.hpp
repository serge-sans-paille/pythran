//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SHUFFLE_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SHUFFLE_HPP_INCLUDED

#include <nt2/swar/functions/shuffle.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::shuffle_, tag::cpu_
                            , (A0)(X)(P)
                            , ((simd_<complex_<arithmetic_<A0> >,X>))
                              (target_< unspecified_<P> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, P const&) const
    {
      typedef typename P::type p_t;
      return result_type( shuffle<p_t>(real(a0)),shuffle<p_t>(imag(a0)) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::shuffle_, tag::cpu_
                            , (A0)(X)(P)
                            , ((simd_<dry_<arithmetic_<A0> >,X>))
                              (target_< unspecified_<P> >)
                            )
  {
    typedef A0                                result_type;
    typedef typename meta::as_real<A0>::type  r_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, P const&) const
    {
      typedef typename P::type p_t;
      return bitwise_cast<result_type>( shuffle<p_t>(bitwise_cast<r_t>(a0)) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::shuffle_, tag::cpu_
                            , (A0)(X)(P)
                            , ((simd_<complex_<arithmetic_<A0> >,X>))
                              ((simd_<complex_<arithmetic_<A0> >,X>))
                              (target_< unspecified_<P> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, P const&) const
    {
      typedef typename P::type p_t;
      return result_type( shuffle<p_t>(real(a0),real(a1))
                        , shuffle<p_t>(imag(a0),imag(a1))
                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::shuffle_, tag::cpu_
                            , (A0)(X)(P)
                            , ((simd_<dry_<arithmetic_<A0> >,X>))
                              ((simd_<dry_<arithmetic_<A0> >,X>))
                              (target_< unspecified_<P> >)
                            )
  {
    typedef A0                                result_type;
    typedef typename meta::as_real<A0>::type  r_t;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, P const&) const
    {
      typedef typename P::type p_t;
      return bitwise_cast<result_type>( shuffle<p_t>( bitwise_cast<r_t>(a0)
                                                    , bitwise_cast<r_t>(a1)
                                                    )
                                      );
    }
  };
} }

#endif
