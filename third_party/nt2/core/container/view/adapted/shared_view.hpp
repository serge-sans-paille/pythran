//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_VIEW_ADAPTED_SHARED_VIEW_HPP_INCLUDED
#define NT2_CORE_CONTAINER_VIEW_ADAPTED_SHARED_VIEW_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>

namespace nt2 { namespace meta
{
  struct table_;
} }

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY : Option of a shared_view use its settings and semantic
  template<typename Kind, typename T, typename S, typename Tag>
  struct  option<container::shared_view<Kind, T, S> , Tag>
        : option<S, Tag, Kind>
  {};

  /// INTERNAL ONLY : add_settinfs to a shared_view
  template<typename Kind, typename T, typename S, typename S2>
  struct add_settings< container::shared_view<Kind, T, S>, S2 >
  {
    typedef typename add_settings<S, S2>::type      sets_t;
    typedef container::shared_view<Kind, T, sets_t> type;
  };

  /// INTERNAL ONLY : Extract settings from shared_view
  template<typename Kind, typename T, typename S>
  struct settings_of< container::shared_view<Kind, T, S> >
  {
    typedef S type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY : value_of for shared_view
  template<typename Kind, typename T, typename S>
  struct value_of< nt2::container::shared_view<Kind, T,S> >
  {
    typedef T type;
  };

  /// INTERNAL ONLY : model_of for shared_view
  template<typename Kind, typename T, typename S>
  struct model_of< nt2::container::shared_view<Kind, T,S> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef nt2::container::shared_view<Kind, X,S> type;
      };
    };
  };

  /// INTERNAL ONLY : semantic_of for shared_view
  template<typename Kind, typename T, typename S>
  struct semantic_of< nt2::container::shared_view<Kind, T, S> >
  {
    typedef typename nt2::container::shared_view<Kind, T, S>::container_type  type;
  };
} } }

#endif
