//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/shuffle.hpp>
#include <boost/simd/swar/functions/details/shuffler.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/patterns.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/permutation.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::sse2_
                                    , (T)(P)
                                    , ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef T  result_type;

    BOOST_FORCEINLINE result_type operator()(T const& a0,P const&) const
    {
      typename P::type p;

      return details::shuffler< sse2_matcher
                              , sse2_permutation<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 8
                              >::process(a0,p);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::sse2_
                                    , (T)(P)
                                    , ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef T  result_type;

    BOOST_FORCEINLINE
    result_type operator()(T const& a0,T const& a1, P const&) const
    {
      typename P::type p;

      return details::shuffler< sse2_matcher
                              , sse2_permutation<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 8
                              >::process(a0,a1,p);
    }
  };
} } }

#endif
#endif
