//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_TAGS_HPP_INCLUDED
#define NT2_SDK_META_TAGS_HPP_INCLUDED

namespace nt2
{
  // tags allowing to choose computation standard for some toolboxes
  struct fast_tag{};        // extra-speed
                            // but very small validity range with trigo
                            //     no rouding for exp2(n) or exp10(n) if n is a flint

  struct accu_tag{};        // full range and precision at expanse of slowness
  struct nt2_tag{};        // nt2 implementation choices
}

#endif
