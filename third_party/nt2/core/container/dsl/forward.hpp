//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_FORWARD_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_FORWARD_HPP_INCLUDED

#include <nt2/core/settings/forward.hpp>

namespace nt2 { namespace tag
{
  struct container_;
} }

namespace nt2
{
  template<class T>
  struct box;
}

namespace nt2 { namespace container
{
  template<bool B> struct extremum;
  struct colon_;

  template<class Domain>  struct generator_transform;
  template<class Domain>  struct size_transform;

  struct domain;

  template<class Expression, class ResultType>
  struct expression;

  template<class Type, class Settings = nt2::settings()>
  struct table;

  template<typename Kind, typename Type, typename Settings = nt2::settings()>
  struct view;

  template<typename Kind, typename Type, typename Settings = nt2::settings()>
  struct shared_view;
} }

#endif
