//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_DETAILS_AT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_DETAILS_AT_ITERATOR_HPP_INCLUDED

#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <climits>

namespace boost { namespace simd
{
  template<typename Seq, int N, int Max = INT_MAX>
  struct at_iterator
      : boost::fusion::
        iterator_facade < at_iterator<Seq, N>
                        , boost::fusion::random_access_traversal_tag
                        >
  {
    BOOST_STATIC_CONSTANT(int index,   = N);
    BOOST_STATIC_CONSTANT(int maximum, = Max);
    typedef Seq sequence_type;

    at_iterator(Seq& seq) : seq_(seq) {}

    Seq& seq_;

    template<typename It>
    struct value_of
      : boost::fusion::result_of::
        value_at_c<typename It::sequence_type, It::index>
    {
    };

    template<typename It>
    struct deref
    {
      typedef typename boost::fusion::result_of::
      at_c< typename It::sequence_type
          , It::index
          >::type                                         type;

      static type call(It const& it) { return boost::fusion::at_c<N>(it.seq_); }
    };

    template<typename It>
    struct next
    {
      typedef at_iterator< typename It::sequence_type
                         , (It::index >= It::maximum) ? It::maximum : (It::index + 1)
                         , It::maximum
                         >                                type;

      static type call(It const& it) { return type(it.seq_); }
    };

    template<typename It>
    struct prior
    {
      typedef at_iterator< typename It::sequence_type
                         , (It::index <= 0) ? 0 : (It::index - 1)
                         , It::maximum
                         >                                type;

      static type call(It const& it) { return type(it.seq_); }
    };

    template<typename It1, typename It2>
    struct distance
    {
      typedef typename boost::mpl::
      int_<It2::index - It1::index>::type                 type;

      static type call(It1 const& , It2 const& ) { return type(); }
    };

    template<typename It, typename M>
    struct advance
    {
      typedef at_iterator< typename It::sequence_type
                         , (It::index + M::value >= It::maximum) ? It::maximum : (It::index + M::value)
                         , It::maximum
                         >                                type;

      static type call(It const& it) { return type(it.seq_); }
    };

    private:
    at_iterator& operator=(at_iterator const&);
  };
} }

#endif
