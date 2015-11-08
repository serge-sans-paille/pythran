//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_COMPLEX_SIMD_COMMON_EXTRACT_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_COMPLEX_SIMD_COMMON_EXTRACT_HPP_INCLUDED

#include <nt2/memory/functions/extract.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::extract_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_< dry_ < arithmetic_<A0> >, X >))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      return bitwise_cast<result_type>(extract(nt2::real(a0), a1));
    }
  };
} }

#endif
