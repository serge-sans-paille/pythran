//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_CARDINAL_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_CARDINAL_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the \ref boost::simd::meta::cardinal_of \metafunction
 */

#include <boost/mpl/size_t.hpp>

namespace boost { namespace simd { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * \metafunction computing the number of values of type \c T to fit in a
   * register.
   *
   * \tparam T Hierarchizable type
   *
   * \par Model:
   *
   * \metafunction
   *
   */
  //============================================================================
  template<class T> struct cardinal_of : boost::mpl::size_t<1> {};

  template<class T> struct cardinal_of<T&>      : cardinal_of<T> {};
  template<class T> struct cardinal_of<T const> : cardinal_of<T> {};

} } }

#endif
