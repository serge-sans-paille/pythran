//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_BUFFER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_BUFFER_HPP_INCLUDED

/*!
  @file
  @brief Defines the buffer_ settings tag
**/

#include <nt2/core/settings/forward/buffer.hpp>
#include <nt2/core/settings/details/is_buffer.hpp>

namespace nt2 { namespace tag
{
  /// @brief Option tag for allocator options
  struct buffer_
  {
    template<class T>
    struct  apply
          : details::is_buffer<T>
    {};

    typedef nt2::built_in_ default_type;
  };

  template<>
  struct  buffer_::apply< nt2::built_in_>
        : boost::mpl::true_
  {};
} }

#include <nt2/core/settings/details/buffer.hpp>

#endif
