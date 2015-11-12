//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_PERMUTE_META_HPP_INCLUDED
#define NT2_SDK_META_PERMUTE_META_HPP_INCLUDED

#include <boost/simd/sdk/details/at_iterator.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/support.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register permute_ expression as fusion random access sequence
  //============================================================================
  template<> struct is_sequence_impl<nt2::tag::permute_>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<> struct is_view_impl<nt2::tag::permute_>
  {
    template<typename Seq> struct apply : mpl::true_ {};
  };

  template<> struct category_of_impl<nt2::tag::permute_>
  {
    typedef random_access_traversal_tag type;
  };

  //============================================================================
  // Size of permute_ is given by its static_size member
  //============================================================================
  template<> struct size_impl<nt2::tag::permute_>
  {
    template<typename Sequence>
    struct  apply
          : boost::fusion::result_of::size<typename Sequence::sequence_type>::type
    {};
  };

  //============================================================================
  // at_c value of permute_ is given by its static size or dynamic size if -1
  //============================================================================
  template<> struct at_impl<nt2::tag::permute_>
  {
    template<class Sequence, class Index>
    struct apply
    {
      typedef typename Sequence::permutation_type perm_type;
      typedef typename Sequence::sequence_type seq_type;
      typedef typename boost::fusion::result_of::size<Sequence>::type size_type;
      typedef typename boost::mpl::apply<perm_type,size_type,Index>::type index_type;
      typedef typename boost::fusion::result_of::at_c<seq_type,index_type::value>::type type;

      static type call(Sequence& seq)
      {
        return at_c<index_type::value>(seq.seq);
      }
    };
  };

  template<> struct value_at_impl<nt2::tag::permute_>
  {
    template<class Sequence, class Index>
    struct apply
    {
      typedef typename Sequence::permutation_type perm_type;
      typedef typename Sequence::sequence_type seq_type;
      typedef typename boost::fusion::result_of::size<Sequence>::type size_type;
      typedef typename boost::mpl::apply<perm_type,size_type,Index>::type index_type;
      typedef typename boost::fusion::result_of::value_at<seq_type,index_type>::type type;
    };
  };

  //==========================================================================
  // begin returns the inner data_type begin as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct begin_impl<nt2::tag::permute_>
  {
    template<typename Sequence, typename Index, typename SO> struct apply
    {
      typedef boost::simd::at_iterator<Sequence, 0> type;
      static type call(Sequence& seq)
      {
        return type(seq);
      }
    };
  };

  //==========================================================================
  // end returns the inner data_type end as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct end_impl<nt2::tag::permute_>
  {
    template<typename Sequence, typename Index, typename SO>
    struct apply
    {
            typedef typename boost::fusion::result_of::size<Sequence>::type size_type;
            typedef boost::simd::at_iterator<Sequence, size_type::value> type;
      static type call(Sequence& seq)
      {
        return type(seq);
      }
    };
  };
} } }

#endif
