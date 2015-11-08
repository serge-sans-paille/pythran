//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_FUSION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_FUSION_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/sdk/meta/is_statically_sized.hpp>
#include <boost/simd/sdk/details/at_iterator.hpp>
#include <boost/fusion/support.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/if.hpp>

////////////////////////////////////////////////////////////////////////////////
// TODO REFRESH TO USE PROPER TYPES ETC...
// TODO MAKE TABLE AND OTHER CONTAINER USE THIS
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  //============================================================================
  /*! Identify expression as valid fusion sequence                            */
  //============================================================================
  struct container_ {};
} }

//==============================================================================
//Implement shared generic Fusion sequence conformance for container expression
//==============================================================================
namespace boost { namespace fusion { namespace traits
{
  template<class Expr, class ResultType>
  struct tag_of< nt2::container::expression<Expr,ResultType> >
  {
    typedef typename
            mpl::if_< nt2::meta::
                      is_statically_sized < nt2::container::
                                            expression<Expr,ResultType>
                                          >
                    , nt2::tag::container_
                    , non_fusion_tag
                    >::type                                     type;
  };
} } }

namespace boost { namespace fusion { namespace extension
{
  //============================================================================
  // Register container expression as fusion random access sequence
  //============================================================================
  template<> struct is_sequence_impl<nt2::tag::container_>
  {
    template<typename T> struct apply : mpl::true_ {};
  };

  template<> struct is_view_impl<nt2::tag::container_>
  {
    template<typename Seq> struct apply : mpl::false_ {};
  };

  template<> struct category_of_impl<nt2::tag::container_>
  {
    typedef random_access_traversal_tag type;
  };

  //============================================================================
  // Size of expression is given by its Dimensions
  //============================================================================
  template<> struct size_impl<nt2::tag::container_>
  {
    template<typename Sequence>
    struct  apply
          : mpl::size_t < dispatch::meta::call<nt2::tag::extent_(Sequence)>
                                  ::type::static_numel
                        >
    {};
  };

  //============================================================================
  // at_c value of expression is given by its operator()
  //============================================================================
  template<> struct at_impl<nt2::tag::container_>
  {
    template<typename Sequence, typename Index>
    struct apply
    {
      typedef typename  mpl::if_< is_const<Sequence>
                                , typename Sequence::const_reference
                                , typename Sequence::reference
                                >::type                             type;

      static type call(Sequence& seq) { return seq(Index::value+1); }
    };
  };

  //==========================================================================
  // begin returns the inner data_type begin as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct begin_impl<nt2::tag::container_>
  {
    template<typename Sequence> struct apply
    {
      typedef boost::simd::at_iterator<Sequence,0> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };

  //==========================================================================
  // end returns the inner data_type end as it is itself a Fusion Sequence
  //==========================================================================
  template<> struct end_impl<nt2::tag::container_>
  {
    template<typename Sequence>
    struct apply
    {
      typedef boost::simd::at_iterator<Sequence, Sequence::static_dimensions> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };
} } }

#endif
