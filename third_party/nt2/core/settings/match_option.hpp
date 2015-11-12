//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_MATCH_OPTION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_MATCH_OPTION_HPP_INCLUDED

/*!
 * \file
 * \brief Defines NT2 container option base system
 **/

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>

namespace nt2 { namespace meta
{
  /*!
   * @brief Check if a type is a valid Option
   *
   **/
  template<class T, class Option>
  struct  match_option
        : Option::template apply<typename boost::remove_pointer<T>::type>::type
  {};

  template<class T, class Option>
  struct  match_option<T*, Option>
        : match_option<T,Option>
  {};

  template<class Option>
  struct lambda_match_option
  {
    template<class T> struct apply : match_option<T,Option> {};
  };
} }

#endif
