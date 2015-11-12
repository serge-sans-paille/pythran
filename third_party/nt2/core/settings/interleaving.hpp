//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_INTERLEAVING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_INTERLEAVING_HPP_INCLUDED

#include <nt2/core/settings/forward/interleaving.hpp>

namespace nt2 { namespace tag
{
  struct interleaving_
  {
    template<class T>
    struct apply : boost::mpl::false_
    {};

    typedef nt2::interleaved_ default_type;
  };

  template<>
  struct interleaving_::apply<nt2::interleaved_>
                      : boost::mpl::true_
  {};

  template<>
  struct interleaving_::apply<nt2::deinterleaved_>
                      : boost::mpl::true_
  {};
} }

#endif
