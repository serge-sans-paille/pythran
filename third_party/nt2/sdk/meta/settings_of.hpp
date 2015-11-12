//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_SETTINGS_OF_HPP_INCLUDED
#define NT2_SDK_META_SETTINGS_OF_HPP_INCLUDED

/*!
  @file
  @brief
**/

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/alignment.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>

namespace nt2
{
  namespace details
  {
    /// INTERNAL ONLY - By default, behave like a Matlab like unaligned scalar value
    template<class T, class Enable = void>
    struct  settings_of
    {
      typedef settings type(matlab_index_, _0D, matlab_order_, unaligned_);
    };

    /// INTERNAL ONLY - Try to find and extract a settings_type from the type
    template<class T>
    struct settings_of< T
                      , typename  boost::dispatch::meta::
                        enable_if_type<typename T::settings_type>::type
                      >
    {
      typedef typename T::settings_type type;
    };
  }

  namespace meta
  {
    /*!
     * Retrieve settings type from a Container
     *
     * \tparam T Container to retrieve settings from
     */
    template<class T> struct settings_of          : details::settings_of<T> {};
    template<class T> struct settings_of<T&>      : settings_of<T> {};
    template<class T> struct settings_of<T const> : settings_of<T> {};
  }
}

#endif
