//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_MPL_VALUE_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_MPL_VALUE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <cstddef>

namespace nt2
{
  //============================================================================
  // If the result of a size computation is a MPL Integral, keep it;
  // If not, return -1 so the of_size will be flagged as dynamic
  //============================================================================
  template<class T, class Enable = void>
  struct mpl_value : boost::mpl::integral_c<std::ptrdiff_t, -1> {};

  template<class T>
  struct mpl_value < T
                   , typename boost::
                     enable_if < boost::dispatch::details::
                                 is_mpl_integral< typename meta::strip<T>::type >
                               >::type
                   >
    : meta::strip<T>::type
  {};

  //============================================================================
  // If the result of a size computation is a MPL Integral, extract its type;
  // If it's an integral type already, return it
  // If not, return std::ptrdiff_t type (case for void_)
  //============================================================================
  template<class T, class Enable = void>
  struct mpl_value_type
  {
    typedef T type;
  };

  template<class T>
  struct mpl_value_type< T
                       , typename boost::
                         enable_if< boost::dispatch::details::
                                    is_mpl_integral<typename meta::strip<T>::type>
                                  >::type
                        >
  {
    // Case for non mpl::void_ basically
    template<class X, class E=void> struct impl
    {
      typedef std::size_t type;
    };

    template<class X>
    struct impl < X , typename meta::
                      enable_if_type< typename meta::strip<T>
                                                    ::type::value_type
                                    >::type
                >
    {
      typedef typename meta::strip<T>::type::value_type type;
    };

    typedef typename impl<T>::type type;
  };
}

#endif
