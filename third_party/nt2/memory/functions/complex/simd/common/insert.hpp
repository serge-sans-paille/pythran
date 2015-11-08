//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_COMPLEX_SIMD_COMMON_INSERT_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_COMPLEX_SIMD_COMMON_INSERT_HPP_INCLUDED

#include <nt2/memory/functions/insert.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::insert_, tag::cpu_, (A0)(A1)(X)(A2)
                            , (scalar_< dry_ < arithmetic_<A0> > >)
                              ((simd_< dry_ < arithmetic_<A1> >, X >))
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2 a2) const
    {
      typedef typename meta::as_real<A1>::type r_t;
      insert(nt2::real(a0), reinterpret_cast<r_t&>(a1), a2);
    }
  };
} }

#endif
