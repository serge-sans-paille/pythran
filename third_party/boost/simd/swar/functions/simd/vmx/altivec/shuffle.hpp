//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/swar/functions/shuffle.hpp>
#include <boost/simd/swar/functions/details/shuffler.hpp>
#include <boost/simd/swar/functions/simd/vmx/altivec/details/permutation.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/swar/functions/details/perm.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::vmx_
                                    , (T)(P)
                                    , ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef T  result_type;

    BOOST_FORCEINLINE result_type operator()(T const& a0,P const&) const
    {
      typename P::type p;

      return details::shuffler< details::default_matcher
                              , details::vmx_permute<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 16
                              >::process(a0,p);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::vmx_
                                    , (T)(P)
                                    , ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      ((simd_ < arithmetic_<T>
                                              , boost::simd::tag::vmx_
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

      return details::shuffler< details::default_matcher
                              , details::vmx_permute<meta::cardinal_of<T>::value>
                              , meta::cardinal_of<T>::value
                              , 16
                              >::process(a0,a1,p);
    }
  };
} } }

#endif
#endif
