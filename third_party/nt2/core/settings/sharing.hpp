//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_SHARING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_SHARING_HPP_INCLUDED

#include <nt2/core/settings/forward/sharing.hpp>

namespace nt2 { namespace tag
{
  struct sharing_
  {
    template<class T>
    struct apply : boost::mpl::false_
    {};

    typedef nt2::owned_ default_type;
  };

  template<>
  struct sharing_::apply<nt2::shared_>
                  : boost::mpl::true_
  {};

  template<>
  struct sharing_::apply<nt2::owned_>
                  : boost::mpl::true_
  {};
} }

#include <nt2/core/settings/details/sharing.hpp>

#endif
