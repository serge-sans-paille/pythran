//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_ALIGNED_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/aligned_store.hpp>
#include <boost/simd/memory/functions/details/char_helper.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_store_
                                      , boost::simd::tag::vmx_
                                      , (A0)(A1)
                                      , ( simd::meta::is_pointing_to
                                          < A1
                                          , typename  dispatch::meta
                                                    ::scalar_of<A0>::type
                                          >
                                        )
                                      , ((simd_ < arithmetic_<A0>
                                                , boost::simd::tag::vmx_
                                                >
                                        ))
                                        (iterator_< scalar_< arithmetic_<A1> > >)
                                      )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(A0));
      vec_st(a0(), 0, char_helper(a1));
    }
  };
} } }

#endif
#endif
