//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_HIERARCHY_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_HIERARCHY_HPP_INCLUDED

/*!
  @file
  @brief Defines the BOOST_SIMD_CONSTANT_IMPLEMENTATION macro
**/
#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/functor/functor.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
    @brief Constant hierarchy
  **/
  template<typename T>
  struct constant_ : elementwise_<T>
  {
    typedef elementwise_<T> parent;
  };

  /*!
    @brief Pure constant hierarchy
  **/
  template<typename T>
  struct pure_constant_ : constant_<T>
  {
    typedef constant_<T> parent;
  };
} } }

namespace boost { namespace simd { namespace ext
{
  using boost::dispatch::meta::constant_;
  using boost::dispatch::meta::pure_constant_;
} } }

//==============================================================================
/*!
 * Generate a constant function with a given c NAME tied to a given constant
 * ID c TAG
 *
 * param TAG ID of the constant to wrap
 * param NAME Name of the function to build
 */
//==============================================================================
#define BOOST_SIMD_CONSTANT_IMPLEMENTATION(TAG,NAME)                           \
template<typename Target> BOOST_FORCEINLINE                                    \
typename boost::dispatch::meta::                                               \
call<TAG(boost::dispatch::meta::as_<Target> const&)>::type                     \
NAME()                                                                         \
{                                                                              \
  typename boost::dispatch::make_functor<TAG, Target>::type callee;            \
  return callee( boost::dispatch::meta::as_<Target>() );                       \
}                                                                              \
template<typename Target> BOOST_FORCEINLINE                                    \
typename boost::dispatch::meta::                                               \
call<TAG(boost::dispatch::meta::as_<Target> const&)>::type                     \
NAME(boost::dispatch::meta::as_<Target> const& tgt)                            \
{                                                                              \
  typename boost::dispatch::make_functor<TAG, Target>::type callee;            \
  return callee( tgt );                                                        \
}
/**/

#endif
