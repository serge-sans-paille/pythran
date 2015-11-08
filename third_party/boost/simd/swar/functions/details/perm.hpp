//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED

#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace details
{
  // Result of the meta permutation
  template<class P, class Card, int I>
  struct index_ : boost::mpl::apply < P
                                    , boost::mpl::int_<I>
                                    , Card
                                    >::type
  {};

  // Generate the the correct mask
  template<class P, class Card, char Offset, char Idx, char Inc>
  struct  generate_
        : boost::mpl::int_<((0>index_<P,Card,Idx>::value)?-1:(Offset+Inc))>
  {};

  template<std::size_t Bytes, int N>
  struct  bit_count
        : boost::mpl::int_< 1 <<  ( boost::static_log2<Bytes>::value
                                  - boost::static_log2<N>::value
                                  )
                          >
  {};

  // Permute specialization
  template<class P, class Type, int N> struct permute
  {
    static const std::size_t Bytes = sizeof(Type);

    template<char I>
    struct  mask_
          : generate_ < P
                      , boost::mpl::int_<N>
                      , index_<P, boost::mpl::int_<N>, (I / (Bytes/N))>::value
                      * bit_count<Bytes,N>::value
                      , I / (Bytes/N)
                      , I % (Bytes/N)
                      >
    {};

    static BOOST_FORCEINLINE Type call()
    {
      return call(boost::mpl::int_<Bytes>());
    }

    static BOOST_FORCEINLINE Type call(boost::mpl::int_<16> const&)
    {
      return make<Type> ( mask_< 0>::value, mask_< 1>::value
                        , mask_< 2>::value, mask_< 3>::value
                        , mask_< 4>::value, mask_< 5>::value
                        , mask_< 6>::value, mask_< 7>::value
                        , mask_< 8>::value, mask_< 9>::value
                        , mask_<10>::value, mask_<11>::value
                        , mask_<12>::value, mask_<13>::value
                        , mask_<14>::value, mask_<15>::value
                        );
    }

    static BOOST_FORCEINLINE Type call(boost::mpl::int_<8> const&)
    {
      return make<Type> ( mask_< 0>::value, mask_< 1>::value
                        , mask_< 2>::value, mask_< 3>::value
                        , mask_< 4>::value, mask_< 5>::value
                        , mask_< 6>::value, mask_< 7>::value
                        );
    }
  };
} } }

#endif
