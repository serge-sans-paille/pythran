//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_COMBINE_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_COMBINE_HPP_INCLUDED

#include <nt2/swar/functions/combine.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::combine_
                            , tag::cpu_
                            , (A0)(X)
                            , ((simd_< complex_< unspecified_<A0> >, X >))
                              ((simd_< complex_< unspecified_<A0> >, X >))
                            )
  {
    typedef typename  boost::simd::meta::vector_of< typename A0::value_type
                                                  , A0::static_size * 2
                                                  >::type           result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return result_type( nt2::combine(real(a0),real(a1))
                        , nt2::combine(imag(a0),imag(a1))
                        );
    }
  };
} }

#endif
