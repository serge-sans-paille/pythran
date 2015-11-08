//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_NO_SEMANTIC_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_NO_SEMANTIC_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/alignment.hpp>

namespace nt2
{
  /// @brief Semantic of non-container object (namely scalars)
  struct no_semantic_
  {
    /// INTERNAL ONLY no_semantic_ usually use whatever the use specify
    template<typename Settings, typename Option>
    struct option
    {
      typedef Settings type;
    };

    /// INTERNAL ONLY no_semantic_ default option
    template<typename Option>
    struct default_
    {
      typedef typename Option::default_type type;
    };
  };

  /// INTERNAL ONLY
  template<>
  struct no_semantic_::default_<nt2::tag::of_size_>
  {
    typedef _0D type;
  };

  /// INTERNAL ONLY
  template<>
  struct no_semantic_::default_<nt2::tag::alignment_>
  {
    typedef unaligned_ type;
  };
}

#endif
