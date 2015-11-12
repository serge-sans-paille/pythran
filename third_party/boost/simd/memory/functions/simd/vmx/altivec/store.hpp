//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/store.hpp>
#include <boost/simd/memory/functions/details/char_helper.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY SIMD unaligned store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::store_
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
    typedef void                              result_type;
    typedef typename boost::pointee<A1>::type value_t;
    typedef typename A0::native_type          n_t;

    static const std::size_t sz   = sizeof(value_t);
    static const std::size_t card = meta::cardinal_of<A0>::value;
    static const std::size_t a2z  = card*sz-1;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, A1 a1) const
    {
      typename char_helper_impl<value_t>::type* ptr = char_helper(a1);

      n_t                     MSQ       = vec_ld  ( 0   , ptr );
      __vector unsigned char  edgeAlign = vec_lvsl( 0   , ptr );
      n_t                     LSQ       = vec_ld  ( a2z , ptr );
      __vector unsigned char  align     = vec_lvsr( 0   , ptr );
      n_t                     edges     = vec_perm( LSQ , MSQ, edgeAlign  );

      MSQ = vec_perm(edges, a0(), align);
      LSQ = vec_perm(a0(), edges, align);

      vec_st(LSQ, a2z, ptr);
      vec_st(MSQ, 0  , ptr);
    }
  };
} } }

#endif
#endif
