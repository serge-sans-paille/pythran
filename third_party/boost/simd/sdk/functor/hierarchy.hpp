//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED
#define BOOST_SIMD_SDK_FUNCTOR_HIERARCHY_HPP_INCLUDED

#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/meta/tieable.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/meta/proxy.hpp>

#include <boost/dispatch/meta/ignore_unused.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    // Sites
    using boost::dispatch::tag::formal_;
    using boost::dispatch::tag::cpu_;
  }

namespace ext
{
  // Base hierarchies
  using boost::dispatch::meta::proxy_;
  using boost::dispatch::meta::unknown_;
  using boost::dispatch::meta::unspecified_;

  // Native types and related hierarchies
  using boost::dispatch::meta::single_;
  using boost::dispatch::meta::double_;

  using boost::dispatch::meta::int8_;  using boost::dispatch::meta::uint8_;  using boost::dispatch::meta::ints8_;
  using boost::dispatch::meta::int16_; using boost::dispatch::meta::uint16_; using boost::dispatch::meta::ints16_;
  using boost::dispatch::meta::int32_; using boost::dispatch::meta::uint32_; using boost::dispatch::meta::ints32_;
  using boost::dispatch::meta::int64_; using boost::dispatch::meta::uint64_; using boost::dispatch::meta::ints64_;

  using boost::dispatch::meta::type8_;
  using boost::dispatch::meta::type16_;
  using boost::dispatch::meta::type32_;
  using boost::dispatch::meta::type64_;

  using boost::dispatch::meta::floating_sized_;
  using boost::dispatch::meta::floating_;

  using boost::dispatch::meta::signed_;
  using boost::dispatch::meta::unsigned_;

  using boost::dispatch::meta::int_;
  using boost::dispatch::meta::uint_;
  using boost::dispatch::meta::integer_;

  using boost::dispatch::meta::arithmetic_;
  using boost::dispatch::meta::bool_;
  using boost::dispatch::meta::fundamental_;

  // Composite hierarchies
  using boost::dispatch::meta::scalar_;
  using boost::dispatch::meta::generic_;
  using boost::dispatch::meta::target_;

  using boost::dispatch::meta::ast_;
  using boost::dispatch::meta::node_;
  using boost::dispatch::meta::expr_;

  using boost::dispatch::meta::array_;
  using boost::dispatch::meta::fusion_sequence_;
  using boost::dispatch::meta::mpl_integral_;

  // Tieable
  using boost::dispatch::meta::tieable_;

  // Function object
  template<class Sig, class Site, class Enable = void>
  struct implement;

  // Helpers
  using boost::dispatch::ignore_unused;

} } }

#endif
