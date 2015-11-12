//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_SHARING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_SHARING_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/memory/fixed_allocator.hpp>
#include <nt2/core/settings/storage_duration.hpp>
#include <boost/dispatch/meta/value_of.hpp>

namespace nt2
{
  /*!
    @brief Memory ownership tag representing shared memory

    This tag indicates that current Container shares its memory with an
    external source to which it delegates the memory handling (including clean
    up of said memory).
  **/
  struct shared_
  {
    template<class Container> struct apply
    {
      typedef typename boost::dispatch::meta::value_of<Container>::type value_t;
      typedef memory::fixed_allocator<value_t>                          alloc_t;
      typedef typename dynamic_::apply<Container,alloc_t>::type         type;
    };
  };

  /*!
    @brief Memory ownership tag representing owned memory

    This tag indicates that current Container owns its own memory and
    handles it on its own, including clean-up of said memory.
  **/
  struct owned_
  {
    template<class Container> struct apply
    {
      typedef typename meta::option<Container,tag::storage_duration_>::type sd_t;
      typedef typename sd_t::storage_duration_type                          sdt_t;
      typedef typename sdt_t::template apply<Container>::type               type;
    };
  };
}

#endif
