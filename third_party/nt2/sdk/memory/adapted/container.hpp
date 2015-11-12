//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_CONTAINER_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY memory::container models Container
  template<typename Kind, typename T, typename S>
  struct is_container< memory::container<Kind, T, S> > : boost::mpl::true_ {};

  /// INTERNAL ONLY Option of a container use its settings and semantic
  template<typename Kind, typename T, typename S, typename Tag>
  struct  option<memory::container<Kind, T, S> , Tag>
        : option<S, Tag, Kind>
  {};

  /// INTERNAL ONLY - Addign option directly to a container
  template<typename Kind, typename T, typename S, typename S2>
  struct add_settings< memory::container<Kind, T, S>, S2 >
  {
    typedef memory::container<Kind, T, typename add_settings<S, S2>::type> type;
  };

  /// INTERNAL ONLY : Extract settings from container
  template<typename Kind, typename T, typename S>
  struct settings_of< memory::container<Kind, T, S> >
  {
    typedef S type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY value_of for container
  template<typename Kind, typename T, typename S>
  struct value_of< nt2::memory::container<Kind, T, S> >
  {
    typedef T type;
  };

  /// INTERNAL ONLY value_of for container reference
  template<typename T,typename S, typename Kind>
  struct value_of< nt2::memory::container<Kind, T, S>& >
  {
    typedef typename nt2::memory::container<Kind, T, S>::reference type;
  };

  /// INTERNAL ONLY value_of for container const refere,ce
  template<typename T,typename S, typename Kind>
  struct value_of< nt2::memory::container<Kind, T, S> const&>
  {
    typedef typename nt2::memory::container<Kind, T, S>::const_reference type;
  };

  /// INTERNAL ONLY model_of for container
  template<typename Kind, typename T, typename S>
  struct model_of< nt2::memory::container<Kind, T, S> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef nt2::memory::container<Kind, X, S> type;
      };
    };
  };

  /// INTERNAL ONLY hierarchy_of for container
  template<typename Kind, typename T, typename S, typename Origin>
  struct hierarchy_of< nt2::memory::container<Kind, T, S>, Origin >
  {
    typedef container_< Kind
                      , typename boost::dispatch::meta
                                                ::property_of<T,Origin>::type
                      , S
                      >                   type;
  };

  /// INTERNAL ONLY container builds a terminal from its semantic
  template<typename Kind, typename T, typename S>
  struct  terminal_of< nt2::memory::container<Kind, T, S> >
        : Kind::template terminal_of<T,S>
  {};
} } }

#endif
