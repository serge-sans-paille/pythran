//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT

#include <boost/simd/swar/functions/shuffle.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/swar/functions/simd/sse/ssse3/details/permutation.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/as.hpp>

//==============================================================================
// SSSE3 shuffle use the SSE2 pattern matcher optimizer but has a specific
// permutation unit that is able to perform single argument permutation. We use
// this for shuffle<?>(a0) and we use bit tricks for the shuffle<?>(a0,a1) case:
// two meta-permutation adapter compute the two part that get bit-ORed.
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
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
                              , ext::sse3_permutation<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 16
                              >::process(a0,p);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::ssse3_
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
                              , ext::sse3_permutation<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 16
                              >::process(a0,a1,p);
    }
  };
} } }

#endif
#endif
