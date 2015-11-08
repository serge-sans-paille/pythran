//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_PERMUTE_VIEW_HPP_INCLUDED
#define NT2_SDK_META_PERMUTE_VIEW_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/mpl/string.hpp>

namespace nt2
{
  namespace tag
  {
    struct permute_ {};
  }

  namespace meta
  {
    /*!
      permute_view_ gives an other view of a sequence.

      @tparam Sequence     Sequence to change the view
      @tparam Permutation  metafunction with rules of the view
   **/
   template<typename Seq, typename Permutation>
    struct permute_view
    {
      typedef Seq sequence_type;
      typedef Permutation permutation_type;
      typedef tag::permute_ fusion_tag;

      permute_view(Seq& s) : seq(s) {}

      Seq& seq;

      private:
      permute_view& operator=(permute_view const& s);
    };

    template <typename Seq, typename Permutation>
    permute_view<Seq,Permutation> permute(Seq const& seq)
    {
      permute_view<Seq,Permutation> that(seq);
      return that;
    }

    template <typename Seq, typename Permutation>
    permute_view<Seq const&,Permutation> permute(Seq const& seq)
    {
      permute_view<Seq const &,Permutation> that(seq);
      return that;
    }
  }
}

#include <nt2/sdk/meta/permute_meta.hpp>

#endif
