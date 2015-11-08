//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_COMPLEX_DETAILS_COMPLEX_FUSION_ADAPT_HPP_INCLUDED
#define NT2_SDK_COMPLEX_DETAILS_COMPLEX_FUSION_ADAPT_HPP_INCLUDED

#include <complex>
#include <boost/simd/sdk/details/at_iterator.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/support.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
  struct std_complex_tag {};

namespace traits
{
  template<class T>
  struct tag_of< std::complex<T> >
  {
    typedef std_complex_tag type;
  };
}
namespace extension
{
  template<> struct is_sequence_impl<std_complex_tag>
  {
    template<class Seq>
    struct apply : mpl::true_
    {
    };
  };

  template<> struct is_view_impl<std_complex_tag>
  {
    template<class Seq>
    struct apply : mpl::false_
    {
    };
  };

  template<> struct category_of_impl<std_complex_tag>
  {
    template<class Seq>
    struct apply
    {
      typedef random_access_traversal_tag type;
    };
  };

  template<> struct value_at_impl<std_complex_tag>
  {
    template<class Sequence, int I>
    struct apply_impl;

    template<class Sequence, class Index>
    struct apply : apply_impl<Sequence, Index::value>
    {
    };

    template<class Sequence>
    struct apply_impl<Sequence, 0>
    {
      typedef typename Sequence::value_type type;
    };

    template<class Sequence>
    struct apply_impl<Sequence, 1>
    {
      typedef typename Sequence::value_type type;
    };
  };

  template<> struct at_impl<std_complex_tag>
  {
    template<class Sequence, int I>
    struct apply_impl;

    template<class Sequence, class Index>
    struct apply : apply_impl<Sequence, Index::value>
    {
    };

    template<class Sequence>
    struct apply_impl<Sequence, 0>
    {
      typedef typename Sequence::value_type type;
      static type call(Sequence& seq)
      {
        return seq.real();
      }
    };

    template<class Sequence>
    struct apply_impl<Sequence, 1>
    {
      typedef typename Sequence::value_type type;
      static type call(Sequence& seq)
      {
        return seq.imag();
      }
    };
  };

  template<> struct size_impl<std_complex_tag>
  {
    template<class Seq>
    struct apply
      : mpl::int_<2>
    {
    };
  };

  template<> struct begin_impl<std_complex_tag>
  {
    template<class Sequence>
    struct apply
    {
      typedef boost::simd::at_iterator<Sequence, 0> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };

  template<> struct end_impl<std_complex_tag>
  {
    template<class Sequence>
    struct apply
    {
      typedef boost::simd::at_iterator<Sequence, 2> type;
      static type call(Sequence& seq) { return type(seq); }
    };
  };
} } }

namespace boost { namespace simd
{
  template<class Tag> struct fusion_has_ctors;
  template<> struct fusion_has_ctors<boost::fusion::std_complex_tag> : boost::mpl::true_ {};
} }

#endif
