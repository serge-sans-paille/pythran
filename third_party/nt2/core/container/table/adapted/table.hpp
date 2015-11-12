//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_ADAPTED_TABLE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_ADAPTED_TABLE_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/meta/settings_of.hpp>

#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY : Option of a table use its settings and semantic
  template<typename T, typename S, typename Tag>
  struct  option<nt2::container::table<T, S> , Tag>
        : option<S, Tag, tag::table_>
  {};

  /// INTERNAL ONLY : add_settings to a table
  template<typename T, typename S, typename S2>
  struct add_settings< container::table<T, S>, S2 >
  {
    typedef container::table<T, typename add_settings<S, S2>::type> type;
  };

  /// INTERNAL ONLY : Extract settings from table
  template<typename T, typename S>
  struct settings_of< container::table<T, S> >
  {
    typedef S type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY : value_of for table
  template<typename T, typename S> struct value_of< nt2::container::table<T,S> >
  {
    typedef T type;
  };

  template<class T, class S>
  struct value_of< nt2::container::table<T,S>& >
  {
    typedef typename nt2::memory::container<nt2::tag::table_,T,S>::reference type;
  };

  template<class T, class S>
  struct value_of< nt2::container::table<T,S> const&>
  {
    typedef typename nt2::memory::container<nt2::tag::table_,T,S>::const_reference type;
  };

  /// INTERNAL ONLY : model_of for table
  template<typename T, typename S>
  struct model_of< nt2::container::table<T,S> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef nt2::container::table<X,S> type;
      };
    };
  };

  /// INTERNAL ONLY : semantic_of for table
  template<typename T, typename S>
  struct semantic_of< nt2::container::table<T, S> >
  {
    typedef nt2::memory::container<nt2::tag::table_,T,S>  type;
  };
} } }

#endif
