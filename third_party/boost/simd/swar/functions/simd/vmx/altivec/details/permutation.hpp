//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_DETAILS_PERMUTATION_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_DETAILS_PERMUTATION_HPP_INCLUDED

#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/swar/functions/details/perm.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  // VMX has a full permute unit
  template<std::size_t N> struct vmx_permute
  {
    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const& p)
    {
      return call(a0,a0,p);
    }

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const& p)
    {
      return call(a0,a1,p,typename details::perform_zeroing<P,N>::type());
    }

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , boost::mpl::true_ const&
                                    )
    {
      typedef typename meta::scalar_of<T>::type                 s_t;
      typedef typename T::template rebind<unsigned char>::type  m_t;

      m_t mask = make<m_t>( details::zero_mask<s_t,P, 0,N>::value
                          , details::zero_mask<s_t,P, 1,N>::value
                          , details::zero_mask<s_t,P, 2,N>::value
                          , details::zero_mask<s_t,P, 3,N>::value
                          , details::zero_mask<s_t,P, 4,N>::value
                          , details::zero_mask<s_t,P, 5,N>::value
                          , details::zero_mask<s_t,P, 6,N>::value
                          , details::zero_mask<s_t,P, 7,N>::value
                          , details::zero_mask<s_t,P, 8,N>::value
                          , details::zero_mask<s_t,P, 9,N>::value
                          , details::zero_mask<s_t,P,10,N>::value
                          , details::zero_mask<s_t,P,11,N>::value
                          , details::zero_mask<s_t,P,12,N>::value
                          , details::zero_mask<s_t,P,13,N>::value
                          , details::zero_mask<s_t,P,14,N>::value
                          , details::zero_mask<s_t,P,15,N>::value
                          );

      T that = vec_and( call(a0,a1,p,boost::mpl::false_())()
                      , bitwise_cast<T>(mask)()
                      );

      return that;
    }

    template<typename T,typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const&
                                    , boost::mpl::false_ const&
                                    )
    {
      typedef typename T::template rebind<unsigned char>::type mask_type;

      T that = vec_perm(a0(),a1(),details::permute<P,mask_type,N>::call()());

      return that;
    }
  };
} } }

#endif
