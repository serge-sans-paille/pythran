//==============================================================================
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_SFINAE_ENABLE_IF_HPP_INCLUDED
#define BOOST_DISPATCH_META_SFINAE_ENABLE_IF_HPP_INCLUDED

#include <boost/dispatch/meta/enable_if_type.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * Provides a SFINAE context to test if a condition is true, and
   * evaluate a meta-function to compute the result type if it is.
   * Evaluating the meta-function also happens in an SFINAE context unlike
   * with \c boost::lazy_enable_if_c.
   *
   * @tparam C Boolean giving the condition
   * @tparam F Meta-Fnction to compute the result type if \c C is true
   *
   **/
  template<bool C, class F, class Enable = void>
  struct sfinae_enable_if_c
  {
  };

  /// INTERNAL ONLY
  template<class F>
  struct sfinae_enable_if_c<true, F, typename boost::dispatch::meta::
                                     enable_if_type<typename F::type>::type
                           >
  {
    typedef typename F::type type;
  };

  /*!
   * Provides a SFINAE context to test if a condition is true, and
   * evaluate a meta-function to compute the result type if it is.
   * Evaluating the meta-function also happens in an SFINAE context unlike
   * with \© boost::lazy_enable_if.
   *
   * @tparam C MPL Integral Constant giving the condition
   * @tparam F Meta-Fnction to compute the result type if \c C is true
   *
   **/
  template<class C, class F>
  struct sfinae_enable_if
       : sfinae_enable_if_c<C::value, F>
  {
  };
} } }

#endif
