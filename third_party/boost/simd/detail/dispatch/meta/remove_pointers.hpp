//==================================================================================================
/*!
  @file

  Defines the remove_pointers meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_REMOVE_POINTERS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_REMOVE_POINTERS_HPP_INCLUDED

namespace boost { namespace dispatch
{
  template<typename T> struct remove_pointers
  {
    using type = T;
  };

  // Fast-lanes for common scenario
  template<typename T> struct remove_pointers<T*>       : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T**>      : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T***>     : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T****>    : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T*****>   : remove_pointers<T> {};

  template<typename T> struct remove_pointers<T*     volatile > : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T**    volatile > : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T***   volatile > : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T****  volatile > : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T***** volatile > : remove_pointers<T> {};

  template<typename T> struct remove_pointers<T*     const> : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T**    const> : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T***   const> : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T****  const> : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T***** const> : remove_pointers<T> {};

  template<typename T> struct remove_pointers<T*      const volatile>  : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T**     const volatile>  : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T***    const volatile>  : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T****   const volatile>  : remove_pointers<T> {};
  template<typename T> struct remove_pointers<T*****  const volatile>  : remove_pointers<T> {};
} }

#endif
