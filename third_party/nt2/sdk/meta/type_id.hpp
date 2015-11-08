//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_TYPE_ID_HPP_INCLUDED
#define NT2_SDK_META_TYPE_ID_HPP_INCLUDED

/**
* @file
* @brief Defines types to string conversion utility functions
**/
#include <nt2/sdk/meta/details/demangle.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <typeinfo>

namespace nt2
{
  /**
    @brief Portable type name demangling function

    For any given type @c T or any value @c x of type @c T, type_id returns
    a @c std::string containing the fully qualified name of type @c T in a
    human readable format including @c const and reference qualifiers.

    @usage

    @include type_id.cpp

    This examples output:

    @code
    char [21]
    float
    std::vector<long*, std::allocator<long*> >
    @endcode

    @return a @c std::string containing the type of @c T
  **/
  template<typename T> inline std::string type_id()
  {
    typedef boost::is_const<typename boost::remove_reference<T>::type>  const_t;
    typedef boost::is_reference<T>                                      ref_t;

    std::string s = details::demangle(typeid(T).name());
    details::add_const(s, boost::mpl::bool_<const_t::value>());
    details::add_ref(s, boost::mpl::bool_<ref_t::value>());
    return s;
  }

  /// @overload
  template<typename T> inline std::string type_id( const T& )
  {
    return type_id<T>();
  }
}

#endif
