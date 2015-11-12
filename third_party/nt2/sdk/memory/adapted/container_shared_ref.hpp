//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_CONTAINER_SHARED_REF_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_CONTAINER_SHARED_REF_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/make_shared.hpp>

#include <nt2/core/settings/option.hpp>
#include <boost/dispatch/meta/terminal_of_shared.hpp>

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY memory::container_shared_ref models Container
  template<typename Kind, typename T, typename S>
  struct  is_container< memory::container_shared_ref<Kind, T, S, true> >
        : boost::mpl::true_ {};

  template<typename Kind, typename T, typename S, bool Own>
  struct  is_container_ref< memory::container_shared_ref<Kind, T, S, Own> >
        : boost::mpl::true_ {};

  /// INTERNAL ONLY Option of a container use its settings and semantic
  template<typename Kind, typename T, typename S, bool Own, typename Tag>
  struct  option<memory::container_shared_ref<Kind, T, S, Own> , Tag>
        : option<S, Tag, Kind>
  {};

  /// INTERNAL ONLY - Adding option directly to a container
  template<typename Kind, typename T, typename S, bool Own, typename S2>
  struct add_settings< memory::container_shared_ref<Kind, T, S, Own>, S2 >
  {
    typedef typename add_settings<S, S2>::type              s_t;
    typedef memory::container_shared_ref<Kind, T, s_t, Own> type;
  };

  /// INTERNAL ONLY : Extract settings from container
  template<typename Kind, typename T, typename S, bool Own>
  struct settings_of< memory::container_shared_ref<Kind, T, S, Own> >
  {
    typedef S type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY value_of for container_shared_ref
  template<typename Kind, typename T, typename S, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Kind, T, S, Own> >
  {
    typedef T& type;
  };

  /// INTERNAL ONLY model_of for container_shared_ref
  template<typename Kind, typename T, typename S, bool Own>
  struct model_of< nt2::memory::container_shared_ref<Kind, T, S, Own> >
  {
    struct type
    {
      template<typename X> struct apply
      {
        typedef nt2::memory::container_shared_ref<X, S, Kind, Own> type;
      };
    };
  };

  /// INTERNAL ONLY hierarchy_of for container_shared_ref
  template<typename Kind, typename T, typename S, bool Own, typename Origin>
  struct hierarchy_of < nt2::memory::container_shared_ref<Kind, T, S, Own>
                      , Origin
                      >
  {
    typedef container_< Kind
                      , typename boost::dispatch::meta
                                      ::property_of<T,Origin>::type
                      , S
                      >                   type;
  };

  /// INTERNAL ONLY terminal_of_shared specialization
  template<typename Kind, typename T, typename S>
  struct terminal_of_shared< nt2::memory::container<Kind, T, S> >
  {
    typedef nt2::memory::container<Kind, T, S>                    container;
    typedef nt2::memory::container_shared_ref<Kind, T, S, true>   container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto::term<container_ref>
                                    , 0
                                    >                             basic_expr;
    typedef nt2::container::expression< basic_expr, container&>   type;

    static type make()
    {
      return type(basic_expr::make(container_ref()));
    }
  };
} } }

#endif
