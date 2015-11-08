//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_ENUMERATE_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_ENUMERATE_HPP_INCLUDED

#include <nt2/swar/functions/enumerate.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::enumerate_, tag::cpu_
                            , (A0)(T)
                            , ((generic_< arithmetic_<A0> >))
                              ((target_< generic_< complex_<arithmetic_<T> > > >))
                            )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      typedef typename meta::as_real<result_type>::type r_t;
      return result_type( enumerate<r_t>(a0) );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::enumerate_, tag::cpu_
                            , (A0)(T)
                            , ((generic_< complex_<arithmetic_<A0> > >))
                              ((target_< generic_< complex_<arithmetic_<T> > > >))
                            )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      typedef typename meta::as_real<result_type>::type r_t;
      return result_type( enumerate<r_t>(nt2::real(a0))
                        , splat<r_t>(nt2::imag(a0))
                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::enumerate_, tag::cpu_
                            , (A0)(A1)(T)
                            , ((generic_< complex_<arithmetic_<A0> > >))
                              ((generic_< complex_<arithmetic_<A1> > >))
                              ((target_< generic_< complex_<arithmetic_<T> > > > ))
                            )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, A1 const& a1, T const& ) const
    {
      typedef typename meta::as_real<result_type>::type r_t;
      return result_type( enumerate<r_t>(real(a0), real(a1))
                        , enumerate<r_t>(imag(a0), imag(a1))
                        );
    }
  };
} }


#endif
