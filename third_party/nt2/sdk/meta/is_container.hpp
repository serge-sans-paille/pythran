//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_IS_CONTAINER_HPP_INCLUDED
#define NT2_SDK_META_IS_CONTAINER_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>

namespace nt2
{
  namespace details
  {
    template<class T, class Enable = void>
    struct is_container : boost::mpl::false_ {};

    template<class T, class Enable = void>
    struct is_container_ref : boost::mpl::false_ {};
  }

  namespace meta
  {
    //==========================================================================
    /*!
     * Checks if a given type satisfy the Container concept.
     *
     * \tparam T Type to qualify as a potential Container
     */
    //==========================================================================
    template<class T>
    struct  is_container
          : details::is_container<T> {};

    template<class T> struct is_container<T&>       : is_container<T> {};
    template<class T> struct is_container<T const>  : is_container<T> {};

    template<class T>
    struct  is_container_ref
          : details::is_container_ref<T> {};

    template<class T> struct is_container_ref<T&>       : is_container_ref<T> {};
    template<class T> struct is_container_ref<T const>  : is_container_ref<T> {};

    template<class T>
    struct  is_container_or_ref
          : boost::mpl::or_< is_container<T>
                           , is_container_ref<T>
                           >
    {
    };

    /*!
      @brief Is an expression a container terminal

      Checks if a given type T is a terminal holding a container.

      @tparam T Type to check
    **/
    template<class T, long Arity = T::proto_arity_c>
    struct is_container_terminal
         : boost::mpl::false_
    {
    };

    /// INTERNAL ONLY
    template<class T>
    struct is_container_terminal<T, 0l>
         : meta::is_container<typename T::proto_child0>
    {
    };
  }
}

#endif
