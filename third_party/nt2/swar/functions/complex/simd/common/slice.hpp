//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SLICE_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_SLICE_HPP_INCLUDED

#include <nt2/swar/functions/slice.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::slice_
                                , tag::cpu_
                                , (A0)(A1)(X)(Y)
                                , ( boost::mpl::bool_
                                    <
                                      A1::static_size == A0::static_size/2
                                    >
                                  )
                                , ((simd_< complex_< unspecified_<A0> >, X >))
                                  ((simd_< complex_< unspecified_<A1> >, Y >))
                                  ((simd_< complex_< unspecified_<A1> >, Y >))
                                )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& a1,A1& a2) const
    {
      typedef typename meta::as_real<A1>::type r_t;

      r_t r1,i1,r2,i2;
      nt2::slice(real(a0),r1,r2);
      nt2::slice(imag(a0),i1,i2);

      a1 = A1(r1,i1);
      a2 = A1(r2,i2);
    }
  };
} }

#endif
