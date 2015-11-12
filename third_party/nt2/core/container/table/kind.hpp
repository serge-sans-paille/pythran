//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_KIND_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_KIND_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/domain.hpp>

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/buffer.hpp>
#include <nt2/core/settings/alignment.hpp>
#include <nt2/core/settings/sharing.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/core/settings/interleaving.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/settings/storage_scheme.hpp>
#include <nt2/core/settings/storage_duration.hpp>
#include <boost/simd/memory/allocator.hpp>

namespace nt2 { namespace tag
{
  /*!
    @brief Table semantic tag

    table_ tag marking a type as using the table semantic and defines
    table default settings
  **/
  struct table_ : nt2::container::domain
  {
    /// INTERNAL ONLY Table usually use whatever the use specify
    template<typename Settings, typename Option>
    struct option
    {
      typedef Settings type;
    };

    /// INTERNAL ONLY Table default option
    template<typename Option>
    struct default_
    {
      typedef typename Option::default_type type;
    };

    /// INTERNAL ONLY How to build a terminal from this semantic
    template<typename Type, typename Settings>
    struct terminal_of
    {
      typedef nt2::container::table<Type, Settings> type;
    };
  };

  /// INTERNAL ONLY Table default option for size
  template<>
  struct table_::default_<nt2::tag::of_size_>
  {
    typedef _4D type;
  };

  /// INTERNAL ONLY Table default option for allocator
  template<>
  struct table_::default_<nt2::tag::allocator_>
  {
    typedef boost::simd::allocator<void> type;
  };
} }

#endif
