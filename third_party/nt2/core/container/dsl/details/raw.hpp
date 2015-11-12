//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_RAW_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_RAW_HPP_INCLUDED

#include <nt2/sdk/memory/forward/container.hpp>

namespace nt2 { namespace details
{
  template<typename T>
  BOOST_FORCEINLINE T* raw(T& t)
  {
    return &t;
  }

  template<typename T>
  BOOST_FORCEINLINE T const* raw(T const& t)
  {
    return &t;
  }

  template<typename Kind, typename T, typename S>
  BOOST_FORCEINLINE typename memory::container_ref<Kind, T, S>::pointer
  raw(memory::container_ref<Kind, T, S> const& c)
  {
    return c.raw();
  }

  template<typename Kind, typename T, typename S>
  BOOST_FORCEINLINE typename memory::container_ref<Kind, T, S>::pointer
  raw(memory::container_ref<Kind, T, S>& c)
  {
    return c.raw();
  }

  template<typename Kind, typename T, typename S, bool Own>
  BOOST_FORCEINLINE
  typename memory::container_shared_ref<Kind, T, S, Own>::pointer
  raw(memory::container_shared_ref<Kind, T, S, Own> const& c)
  {
    return c.raw();
  }

  template<typename Kind, typename T, typename S, bool Own>
  BOOST_FORCEINLINE
  typename memory::container_shared_ref<Kind, T, S, Own>::pointer
  raw(memory::container_shared_ref<Kind, T, S, Own>& c)
  {
    return c.raw();
  }

  template<typename Kind, typename T, typename S>
  BOOST_FORCEINLINE typename memory::container<Kind, T, S>::pointer
  raw(memory::container<Kind, T, S>& c)
  {
    return c.raw();
  }

  template<typename Kind, typename T, typename S>
  BOOST_FORCEINLINE typename memory::container<Kind, T, S>::const_pointer
  raw(memory::container<Kind, T, S> const& c)
  {
    return c.raw();
  }
} }

#endif
