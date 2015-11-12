//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_HIERARCHY_OF_HPP_INCLUDED
#define NT2_SDK_META_HIERARCHY_OF_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/meta/proxy.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2
{
  namespace meta
  {
    using boost::dispatch::meta::hierarchy_of;
  }

namespace ext
{
  //============================================================================
  // Basic hierarchies to be forwarded here
  //============================================================================
  using boost::dispatch::meta::generic_;
  using boost::dispatch::meta::scalar_;
  using boost::dispatch::meta::unspecified_;
  using boost::dispatch::meta::fundamental_;
  using boost::dispatch::meta::bool_;
  using boost::dispatch::meta::void_;
  using boost::dispatch::meta::arithmetic_;
  using boost::dispatch::meta::integer_;
  using boost::dispatch::meta::unsigned_;
  using boost::dispatch::meta::signed_;
  using boost::dispatch::meta::floating_;
  using boost::dispatch::meta::int_;
  using boost::dispatch::meta::uint_;
  using boost::dispatch::meta::type8_;
  using boost::dispatch::meta::type16_;
  using boost::dispatch::meta::floating_sized_;
  using boost::dispatch::meta::type32_;
  using boost::dispatch::meta::type64_;
  using boost::dispatch::meta::ints8_;
  using boost::dispatch::meta::ints16_;
  using boost::dispatch::meta::ints32_;
  using boost::dispatch::meta::ints64_;
  using boost::dispatch::meta::int8_;
  using boost::dispatch::meta::int16_;
  using boost::dispatch::meta::int32_;
  using boost::dispatch::meta::int64_;
  using boost::dispatch::meta::uint8_;
  using boost::dispatch::meta::uint16_;
  using boost::dispatch::meta::uint32_;
  using boost::dispatch::meta::uint64_;
  using boost::dispatch::meta::double_;
  using boost::dispatch::meta::single_;
  using boost::dispatch::meta::long_double_;

  using boost::dispatch::meta::ast_;
  using boost::dispatch::meta::node_;
  using boost::dispatch::meta::expr_;

  using boost::dispatch::meta::proxy_;
} }

#endif
