//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_BUFFER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_BUFFER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/sharing.hpp>

namespace nt2 { namespace details
{
  /// If a Buffer type is provided, return it directly
  template<class T> struct make_buffer
  {
    template<class Container> struct apply { typedef T type; };
  };

  /// If not, build up the buffer manually from the user-defined settings.
  template<> struct make_buffer<nt2::built_in_>
  {
    template<class Container> struct apply
    {
      typedef typename meta::option<Container,tag::sharing_>::type sharing_t;
      typedef typename sharing_t::template apply<Container>::type  type;
    };
  };
} }

#endif
