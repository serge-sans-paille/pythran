//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_VMX_ALTIVEC_ANY_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_VMX_ALTIVEC_ANY_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/reduction/functions/any.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::any_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef typename meta::as_logical<typename A0::value_type>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::any( is_nez(a0) );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::any_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_ < logical_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                    )
  {
    typedef typename meta::as_logical<typename A0::value_type>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return result_type( vec_any_eq( a0(), True<A0>()() ) );
    }
  };
} } }

#endif
#endif
