//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_FUSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_FUSION_HPP_INCLUDED

#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/tag_of_fwd.hpp>
#include <boost/simd/sdk/simd/pack/fusion_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register pack as a fusion sequence
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace tag
{
  struct pack_;
} } }

namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register pack as fusion random access sequence
  //============================================================================
  template<> struct is_sequence_impl<boost::simd::tag::pack_>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<> struct is_view_impl<boost::simd::tag::pack_>
  {
    template<typename Seq> struct apply : mpl::false_ {};
  };

  template<> struct category_of_impl<boost::simd::tag::pack_>
  {
    template<typename Seq>
    struct apply
    {
      typedef random_access_traversal_tag type;
    };
  };

  //============================================================================
  // Size of pack is given by its cardinal
  //============================================================================
  template<> struct size_impl<boost::simd::tag::pack_>
  {
    template<typename Sequence>
    struct  apply
          : boost::mpl::int_< boost::simd::meta::cardinal_of<Sequence>::value >
    {};
  };

  //============================================================================
  // at_c value of pack is given by its operator[]
  //============================================================================
  template<> struct at_impl<boost::simd::tag::pack_>
  {
    template<typename Sequence, typename Index>
    struct apply
    {
      typedef typename  mpl::if_< is_const<Sequence>
                                , typename Sequence::const_reference
                                , typename Sequence::reference
                                >::type                             type;

      static type call(Sequence& seq) { return seq[Index::value]; }
    };
  };

  //============================================================================
  // value_at value of pack given operator[] as a non cref-qualified value
  //============================================================================
  template<> struct value_at_impl<boost::simd::tag::pack_>
  {
    template<typename Sequence, typename Index>
    struct apply
    {
      typedef typename Sequence::value_type type;
    };
  };

  //==========================================================================
  // begin returns the inner data_type begin as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct begin_impl<boost::simd::tag::pack_>
  {
    template<typename Sequence> struct apply
    {
      typedef typename boost::simd::details::fusion_iterator<Sequence,0> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };

  //==========================================================================
  // end returns the inner data_type end as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct end_impl<boost::simd::tag::pack_>
  {
    template<typename Sequence>
    struct apply
    {
      typedef typename  boost::simd::details::
                        fusion_iterator< Sequence
                                       , boost::simd::meta::cardinal_of<Sequence>::value
                                       > type;

      static type call(Sequence& seq) { return type(seq); }
    };
  };
} } }


#endif /* BOOST_SIMD_SDK_SIMD_PACK_FUSION_HPP_INCLUDED */
