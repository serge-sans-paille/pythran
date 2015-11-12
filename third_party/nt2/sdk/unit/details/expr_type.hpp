//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_EXPR_TYPE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_EXPR_TYPE_HPP_INCLUDED

#include <nt2/sdk/meta/type_id.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Wrap a lambda function call into a identity block for display purpose
  template<typename Lambda, typename T>
  boost::mpl::identity<typename boost::mpl::apply<Lambda, T>::type>
  expr_type(T const&)
  {
    return boost::mpl::identity<typename boost::mpl::apply<Lambda, T>::type>();
  }

  /// INTERNAL ONLY
  /// Return a boolean indicating if a given type T is the same as a given
  /// meta-function typename application
  template<typename T, typename U>
  typename boost::is_same<T, typename U::type>::type is_same_as(U const&)
  {
    return typename boost::is_same<T, typename U::type>::type();
  }

  /// INTERNAL ONLY
  /// Display a type from an identity block
  template<typename T> std::string type_id_identity(T const&)
  {
    return nt2::type_id<typename T::type>();
  }

  /// INTERNAL ONLY - Remove MSVC W4 spurrious warning
  template<typename Target> inline void
  check_type_equality( boost::mpl::true_ const& )
  {
    std::cout << " **passed**\n\n";
  }

  /// INTERNAL ONLY - Remove MSVC W4 spurrious warning
  template<typename Target> inline void
  check_type_equality( boost::mpl::false_ const& )
  {
    nt2::unit::error_count()++;
    std::cout << " **failed** is `" << nt2::type_id<Target>() << "`\n\n";
  }

  /// INTERNAL ONLY - Remove MSVC W4 spurrious warning
  template<typename Target> inline void
  check_expr_equality( Target const&, boost::mpl::true_ const& )
  {
    std::cout << " **passed**\n\n";
  }

  /// INTERNAL ONLY - Remove MSVC W4 spurrious warning
  template<typename Target> inline void
  check_expr_equality( Target const& t, boost::mpl::false_ const& )
  {
    nt2::unit::error_count()++;
    std::cout << " **failed**     is `"
              << nt2::details::type_id_identity(t)
              << "`\n\n";
  }
} }

#endif
