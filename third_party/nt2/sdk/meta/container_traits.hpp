//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_CONTAINER_TRAITS_HPP_INCLUDED
#define NT2_SDK_META_CONTAINER_TRAITS_HPP_INCLUDED

#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <cstddef>
#include <memory>

namespace nt2 { namespace tag { struct table_; } }

namespace nt2 { namespace meta
{
  //==============================================================================
  //==============================================================================
  template<typename T, typename Enable = void>
  struct kind_
  {
    typedef tag::table_ type;
  };


  template<typename T>
  struct kind_ < T
                , typename  boost::dispatch::meta::
                            enable_if_type<typename T::kind_type>::type
                >
  {
    typedef typename T::kind_type type;
  };

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void> struct size_type_
  {
    typedef std::size_t type;
  };

  template<class T> struct size_type_<T&> : size_type_<T> {};

   //==============================================================================
   //==============================================================================
  template<class T,class Enable=void> struct allocator_type_
  {
    typedef std::allocator<T> type;
  };

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void>
  struct pointer_
    : boost::add_pointer< typename boost::dispatch::meta::
                          scalar_of<T>::type
                        >
  {
  };

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void>
  struct  const_pointer_
    : boost::add_pointer< typename boost::dispatch::meta::
                          scalar_of<T>::type const
                        >
  {
  };

  template<class T> struct pointer_<T const> : const_pointer_<T> {};
  template<class T> struct pointer_<T&> : pointer_<T> {};
  template<class T> struct const_pointer_<T&> : pointer_<T> {};

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void>
  struct reference_ : boost::dispatch::meta::scalar_of<T&>
  {};

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void>
  struct  const_reference_ : boost::dispatch::meta::scalar_of<T const&>
  {
  };

  template<class T> struct reference_<T const> : const_reference_<T> {};
  template<class T> struct reference_<T&> : reference_<T> {};
  template<class T> struct const_reference_<T&> : reference_<T> {};

  //==============================================================================
  //==============================================================================
  template<class T, class Enable=void>
  struct value_type_
   : boost::dispatch::meta::scalar_of<T>
  {
  };
  template<class T> struct value_type_<T&> : value_type_<T> {};
  template<class T> struct value_type_<T const> : value_type_<T> {};

  template<class T>
  struct allocator_type_< T
                        , typename  boost::dispatch::meta::
                          enable_if_type< typename T::allocator_type >::type
                        >
  {
    typedef typename T::allocator_type type;
  };

  template<class T>
  struct size_type_ < T
                  , typename  boost::dispatch::meta::
                    enable_if_type< typename T::size_type >::type
                  >
  {
    typedef typename T::size_type type;
  };

  template<class T>
  struct pointer_ < T
                  , typename  boost::dispatch::meta::
                    enable_if_type< typename T::pointer
                                  , typename boost::disable_if< boost::is_const<T> >::type
                                  >::type
                  >
  {
    typedef typename T::pointer type;
  };

  template<class T>
  struct const_pointer_ < T
                  , typename  boost::dispatch::meta::
                    enable_if_type< typename T::const_pointer >::type
                  >
  {
    typedef typename T::const_pointer type;
  };
} }

#endif
