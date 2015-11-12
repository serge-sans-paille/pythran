//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_CONTAINER_REF_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_CONTAINER_REF_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY memory::container_ref models ContainerReference
  template<typename Kind, typename T, typename S>
  struct  is_container_ref< memory::container_ref<Kind, T, S> >
        : boost::mpl::true_
  {};

  /// INTERNAL ONLY Option of a container use its settings and semantic
  template<typename Kind, typename T, typename S, typename Tag>
  struct  option<memory::container_ref<Kind, T, S> , Tag>
        : option<S, Tag, Kind>
  {};

  /// INTERNAL ONLY - Adding option directly to a container_ref
  template<typename Kind, typename T, typename S, typename S2>
  struct add_settings< memory::container_ref<Kind, T, S>, S2 >
  {
    typedef typename add_settings<S, S2>::type  s_t;
    typedef memory::container_ref<Kind,T,s_t>   type;
  };

  /// INTERNAL ONLY : Extract settings from container_ref
  template<typename Kind, typename T, typename S>
  struct settings_of< memory::container_ref<Kind, T, S> >
  {
    typedef S type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY value_of for container_ref
  template<typename Kind, typename T, typename S>
  struct value_of< nt2::memory::container_ref<Kind, T, S> >
  {
    typedef T& type;
  };

  /// INTERNAL ONLY model_of for container_ref
  template<typename Kind, typename T, typename S>
  struct model_of< nt2::memory::container_ref<Kind, T, S> >
  {
    struct type
    {
      template<typename X> struct apply
      {
        typedef nt2::memory::container_ref<Kind, X, S> type;
      };
    };
  };

  /// INTERNAL ONLY hierarchy_of for container_ref
  template<typename Kind, typename T, typename S, typename Origin>
  struct hierarchy_of< nt2::memory::container_ref<Kind, T, S>, Origin >
  {
    typedef container_< Kind
                      , typename boost::dispatch::meta
                                                ::property_of<T,Origin>::type
                      , S
                      >                   type;
  };

  /// INTERNAL ONLY container builds a terminal from its semantic
  template<typename Kind, typename T, typename S>
  struct  terminal_of< nt2::memory::container_ref<Kind, T, S> >
        : Kind::template terminal_of<T,S>
  {};
} } }

#endif
