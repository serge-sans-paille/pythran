//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_ALLOCATOR_HPP_INCLUDED
#define NT2_CORE_SETTINGS_ALLOCATOR_HPP_INCLUDED

/*!
  @file
  @brief Defines allocator_ setting behavior
**/

#include <nt2/core/settings/forward/allocator.hpp>
#include <nt2/core/settings/details/has_rebind.hpp>

namespace nt2 { namespace tag
{
  /// @brief Option tag for allocator options
  struct allocator_
  {
    template<class T>
    struct  apply
          : details::has_rebind<T>
    {};
  };
} }

#endif
