//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_FUSION_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_FUSION_ITERATOR_HPP_INCLUDED

#include <boost/fusion/iterator/iterator_facade.hpp>

namespace boost { namespace simd { namespace details
{
  template<typename Seq, int N>
  struct fusion_iterator
      : boost::fusion::
              iterator_facade < fusion_iterator<Seq, N>
                              , boost::fusion::random_access_traversal_tag
                              >
  {
    BOOST_STATIC_CONSTANT(int index, = N );
    typedef Seq sequence_type;

    fusion_iterator(Seq& seq) : seq_(seq) {}

    Seq& seq_;

    template<typename T> struct value_of
    {
      typedef typename T::sequence_type::value_type  type;
    };

    template<typename T> struct deref
    {
      typedef typename
          boost::mpl::if_ < boost::is_const<typename T::sequence_type>
                          , typename T::sequence_type::const_reference
                          , typename T::sequence_type::reference
                          >::type                             type;

      static type call(T const& iter) { return iter.seq_[T::index]; }
    };

    template<typename It> struct next
    {
      typedef fusion_iterator < typename It::sequence_type
                              , It::index + 1
                              >                                type;

      static type call(It const& it) { return type(it.seq_); }
    };

    template<typename It> struct prior
    {
      typedef fusion_iterator < typename It::sequence_type
                              , It::index - 1
                              >                                type;

      static type call(It const& it) { return type(it.seq_); }
    };

    template<typename It1, typename It2>
    struct distance
    {
      typedef typename
              boost::mpl::int_ < It2::index - It1::index>::type type;

      static type call(It1 const&, It2 const&) { return type(); }
    };

    template<typename It, typename M> struct advance
    {
      typedef fusion_iterator < typename It::sequence_type
                              , It::index + M::value
                              >                                type;

      static type call(It const& it) { return type(it.seq_); }
    };
  };
} } }

#endif /* BOOST_SIMD_SDK_SIMD_PACK_FUSION_ITERATOR_HPP_INCLUDED */




