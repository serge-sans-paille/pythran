//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_DEMANGLE_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_DEMANGLE_HPP_INCLUDED

#if (__GNUC__ && __cplusplus && __GNUC__ >= 3)
#include <cxxabi.h>
#endif

#include <string>
#include <cstdlib>
#include <boost/mpl/bool.hpp>

namespace nt2 {  namespace details
{
  /// INTERNAL ONLY
  /// demangle a type name retrieved through typeid()
  inline std::string demangle(const char* name)
  {
    #if(__GNUC__ && __cplusplus && __GNUC__ >= 3)
    std::size_t len;
    int         stat;

    char* realname = ::abi::__cxa_demangle(name,NULL,&len,&stat);

    if(realname != NULL)
    {
      std::string out(realname);
      ::free(realname);
      return out;
    }
    else
    {
      return std::string("?");
    }
    #else
    std::string out(name);
    return out;
    #endif
  }
  /// INTERNAL ONLY
  /// Prevent spurrious warning on MSVC
  inline void add_const(std::string& s, boost::mpl::true_ const&)
  {
    s += " const";
  }

  /// INTERNAL ONLY
  /// Prevent spurrious warning on MSVC
  inline void add_ref(std::string& s, boost::mpl::true_ const&)
  {
    s += "&";
  }

  /// INTERNAL ONLY
  /// Prevent spurrious warning on MSVC
  inline void add_const(std::string&, boost::mpl::false_ const&) {}

  /// INTERNAL ONLY
  /// Prevent spurrious warning on MSVC
  inline void add_ref(std::string&, boost::mpl::false_ const&) {}
} }

#endif
