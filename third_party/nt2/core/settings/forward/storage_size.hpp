//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_STORAGE_SIZE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_STORAGE_SIZE_HPP_INCLUDED

#include <boost/mpl/int.hpp>
#include <nt2/core/settings/forward/storage_duration.hpp>

namespace nt2
{
  /// @brief Row major storage option
  template<std::ptrdiff_t Size>
  struct storage_size_
  {
    /// INTERNAL ONLY
    typedef boost::mpl::integral_c<std::size_t,Size>  storage_size_type;
    typedef nt2::automatic_                           storage_duration_type;
  };

  /// INTERNAL ONLY
  template<> struct storage_size_<-1>
  {
    /// INTERNAL ONLY
    typedef boost::mpl::integral_c<std::size_t,0ULL>  storage_size_type;
    typedef nt2::dynamic_                             storage_duration_type;
  };

  namespace tag
  {
    /// @brief Option tag for the storage order options
    struct storage_size_;
  }
}

#endif
