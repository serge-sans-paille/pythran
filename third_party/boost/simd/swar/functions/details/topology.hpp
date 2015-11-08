//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Adapt a permutation of [C ... 2*C[ to be into [0 ... C[
  //============================================================================
  template<typename Permutation, std::size_t Cardinal>
  struct remap
  {
    template<typename I, typename C>
    struct  apply
          : boost::mpl::int_
            < mpl::apply<Permutation,I,C>::type::value
            - int(Cardinal)*( mpl::apply<Permutation,I,C>::type::value > -1 )
            >
    {};
  };

  //============================================================================
  // Adapt a permutation of [0 ... 2*C[ to be into the [0 ... C[
  //============================================================================
  template<typename Permutation, std::size_t Cardinal>
  struct clamp
  {
    template<typename I, typename C>
    struct  apply
          : boost::mpl::int_
            < (mpl::apply<Permutation,I,C>::type::value >= C::value)
            ? (mpl::apply<Permutation,I,C>::type::value - C::value)
            : mpl::apply<Permutation,I,C>::type::value
            >
    {};
  };
  //============================================================================
  // Adapt a permutation to be remove all -1
  //============================================================================
  template<typename Permutation>
  struct fix_zero
  {
    template<typename I, typename C>
    struct  apply
          : boost::mpl::int_
            < (mpl::apply<Permutation,I,C>::type::value >= 0)
            ? mpl::apply<Permutation,I,C>::type::value
            : I::value
            >
    {};
  };

  //============================================================================
  // Check if Permutation indexing I is forcing a zero
  //============================================================================
  template< typename Permutation, typename Index, typename Cardinal>
  struct  is_zeroing_at
        : mpl::bool_< mpl::apply<Permutation,Index,Cardinal>::type::value == -1 >
  {};

  //============================================================================
  // Does the permutation does any zeroing ?
  //============================================================================
  template<typename Permutation, std::size_t Cardinal>
  struct  perform_zeroing
        : dispatch::meta::any_seq < is_zeroing_at < Permutation
                                                  , boost::mpl::_1
                                                  , mpl::int_<Cardinal>
                                                  >
                                  , mpl::range_c<int,0,Cardinal>
                                  >
  {};

  //============================================================================
  // Zeroing mask generator
  //============================================================================
  template<typename T, typename Permutation, std::size_t Index, std::size_t Cardinal>
  struct  zero_mask
        : mpl::int_< mpl::apply < Permutation
                                , mpl::int_<Index/sizeof(T)>
                                , mpl::int_<Cardinal>
                                >::type::value == -1
                    ? 0 : ~0
                    >
  {};

  //============================================================================
  // Predefined topology
  //============================================================================
  typedef boost::mpl::int_<-1> first_arg;
  typedef boost::mpl::int_< 0> mixed_arg;
  typedef boost::mpl::int_< 1> second_arg;

  //============================================================================
  // Computes the topology of a permutation:
  // -1 means all indexing is from a0
  //  0 means all indexing are random
  // +1 means all indexing is from a1
  //============================================================================
  template<typename Permutation, std::size_t Cardinal>
  struct topology
  {
    typedef mixed_arg type;
  };

  #define M0(z,n,t) static const int i##n = permuted<Permutation,n,t>::value;
  #define M1(z,n,t) && !(i##n>=t)
  #define M2(z,n,t) && (i##n>=t||i##n==-1)

  #define M3(z,n,t)                                                            \
  template<typename Permutation> struct topology<Permutation,n>                \
  {                                                                            \
    BOOST_PP_REPEAT(n,M0,n);                                                   \
                                                                               \
    typedef boost::mpl::                                                       \
            int_< true BOOST_PP_REPEAT(n,M1,n)                                 \
                ? -1 : (true BOOST_PP_REPEAT(n,M2,n) ? 1 : 0)                  \
                > type;                                                        \
  };                                                                           \
  /**/

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM(2,M3,~)

  #undef M0
  #undef M1
  #undef M2
  #undef M3
} } }

#endif
