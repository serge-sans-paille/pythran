//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_REDUCTION_HIERARCHY_HPP_INCLUDED
#define NT2_SDK_META_REDUCTION_HIERARCHY_HPP_INCLUDED

#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace ext
{
  //==========================================================================
  /*!
   * Reduction operations have a hierarchy made out of their actual tag,
   * associated non-reductive operator and a fucntor outputing the neutral
   * element.
   *
   * Once done, they go to unspecified_ as we don't know how to deal with them
   */
  //==========================================================================
  //FIXME nt2::ext::reduction_ is already defined in boost simd module
  // template<class Tag, class Op, class Neutral>
  // struct reduction_ : unspecified_<Tag>
  // {
  //   typedef unspecified_<Tag> parent;
  // };

  //==========================================================================
  /*!
   * Global Reduction operations have a hierarchy made out of their actual tag,
   * associated non-reductive operator and a fucntor outputing the neutral
   * element. They're separated from Reduction for optimization purpose.
   *
   * Once done, they go to unspecified_ as we don't know how to deal with them
   */
  //==========================================================================
  template<class Tag, class Op, class Neutral>
  struct global_reduction_ : unspecified_<Tag>
  {
    typedef unspecified_<Tag> parent;
  };
} }

#endif
