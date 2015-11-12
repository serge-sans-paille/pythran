//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/memory/functions/details/char_helper.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD unaligned load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_
                                      , boost::simd::tag::vmx_
                                      , (A0)(A2)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< arithmetic_<A0> > >)
                                        ((target_
                                          < simd_ < arithmetic_<A2>
                                                  , boost::simd::tag::vmx_
                                                  >
                                          >
                                        ))
                                      )
  {
    typedef typename A2::type                 result_type;
    typedef typename boost::pointee<A0>::type value_t;
    typedef typename result_type::native_type n_t;

    static const std::size_t sz   = sizeof(value_t);
    static const std::size_t card = meta::cardinal_of<result_type>::value;
    static const std::size_t cdz  = card*sz-1;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      typename char_helper_impl<value_t>::type* ptr = char_helper(a0);

      n_t                     MSQ  = vec_ld   ( 0   , ptr );
      __vector unsigned char  mask = vec_lvsl ( 0   , ptr );
      n_t                     LSQ  = vec_ld   ( cdz , ptr );

      return vec_perm(MSQ, LSQ, mask);
    }
  };
} } }

#endif
#endif
