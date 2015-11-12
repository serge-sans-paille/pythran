//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_FUSION_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_FUSION_HPP_INCLUDED


#include <nt2/core/settings/size.hpp>
#include <boost/simd/sdk/details/at_iterator.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/support.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register of_size_ as fusion random access sequence
  //============================================================================
  template<> struct is_sequence_impl<nt2::tag::of_size_>
  {
    template<typename Seq> struct apply : mpl::true_ {};
  };

  template<> struct is_view_impl<nt2::tag::of_size_>
  {
    template<typename Seq> struct apply : mpl::false_ {};
  };

  template<> struct category_of_impl<nt2::tag::of_size_>
  {
    template<typename Seq>
    struct apply
    {
      typedef random_access_traversal_tag type;
    };
  };

  //============================================================================
  // Size of of_size_ is given by its static_size member
  //============================================================================
  template<> struct size_impl<nt2::tag::of_size_>
  {
    template<typename Seq> struct apply : mpl::size_t<Seq::static_size> {};
  };

  //============================================================================
  // at_c value of of_size_ is given by its static size or dynamic size if negative
  // always return 1 if accessed past-the-end
  //============================================================================
  template<> struct at_impl<nt2::tag::of_size_>
  {
    template<class Seq, class Index, std::size_t S, bool B = !(std::size_t(Index::value) >= S)>
    struct select_apply;

    template<class Seq, class Index, std::ptrdiff_t N, bool IsStatic = (N >= 0)>
    struct apply_impl;

    template<class Seq, class Index>
    struct  apply
          : select_apply<Seq, Index, Seq::static_size>
    {};

    template<class Seq, class Index, std::size_t S>
    struct  select_apply<Seq, Index, S, true>
          : apply_impl< Seq, Index
                      , mpl::at<typename Seq::values_type, Index>::type::value
                      >
    {};

    template<class Seq, class Index, std::size_t S>
    struct select_apply<Seq, Index, S, false>
    {
      typedef mpl::size_t<1> type;
      static type call(Seq&) { return type(); }
    };

    template<class Seq, class Index, std::ptrdiff_t N>
    struct apply_impl<Seq, Index, N, false>
    {
      typedef typename mpl::if_ < is_const<Seq>
                                , std::size_t const&
                                , std::size_t&
                                >::type               type;

      static type call(Seq& seq) { return seq.data()[Index::value]; }
    };

    template<class Seq, class Index, std::ptrdiff_t N, bool IsStatic>
    struct apply_impl
    {
      typedef mpl::size_t<N> type;
      static type call(Seq&) { return type(); }
    };
  };

  template<> struct value_at_impl<nt2::tag::of_size_>
  {
    template<class Seq, class Index>
    struct apply
    {
      typedef typename  at_impl<nt2::tag::of_size_>
                        ::template apply<Seq, Index>::type  base;
      typedef typename remove_reference<base>::type         type;
    };
  };

  //==========================================================================
  // begin returns the inner data_type begin as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct begin_impl<nt2::tag::of_size_>
  {
    template<typename Sequence> struct apply
    {
      typedef boost::simd::at_iterator<Sequence, 0, Sequence::static_size> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };

  //==========================================================================
  // end returns the inner data_type end as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct end_impl<nt2::tag::of_size_>
  {
    template<typename Sequence>
    struct apply
    {
      typedef boost::simd::at_iterator<Sequence, Sequence::static_size, Sequence::static_size> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };
} } }

#endif
