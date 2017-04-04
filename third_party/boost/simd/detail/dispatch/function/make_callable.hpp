//==================================================================================================
/*!
  @file

  Provides the callable object registration macro

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_FUNCTION_MAKE_CALLABLE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_FUNCTION_MAKE_CALLABLE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/function/functor.hpp>
#include <boost/simd/detail/dispatch/hierarchy/base.hpp>
#include <boost/simd/detail/dispatch/detail/auto_decltype.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <boost/config.hpp>

/*!
  @ingroup group-function

  Generates the boilerplate code for adapting a @c TAG type as a Boost.Dispatch callable
  object

  @par Usage:

  @param TAG    Tag type to be implemented
  @param PARENT Tag's parent hierarchy
**/
#define BOOST_DISPATCH_MAKE_CALLABLE(NS,TAG,PARENT)                                                 \
template<typename... Args>                                                                          \
static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch_to(Args&&... args) BOOST_NOEXCEPT             \
BOOST_AUTO_DECLTYPE_BODY( BOOST_DISPATCH_DISPATCHING_FUNCTION(TAG)                                  \
                          (NS::adl_helper(), std::forward<Args>(args)...)                           \
                        )                                                                           \
using parent = PARENT                                                                               \
/**/

/*!
  @ingroup group-function

  Generates the boilerplate code for generating a @c TAG type as
  a Boost.Dispatch callable object

  @par Usage:

  @param TAG    Tag type to be implemented
  @param PARENT Tag's parent hierarchy
**/
#define BOOST_DISPATCH_MAKE_TAG(NS,TAG, PARENT)                                                     \
struct TAG : BOOST_PP_REMOVE_PARENS(PARENT)                                                         \
{                                                                                                   \
  BOOST_DISPATCH_MAKE_CALLABLE(NS,TAG,BOOST_PP_REMOVE_PARENS(PARENT));                              \
}                                                                                                   \
/**/

/*!
  @ingroup group-function

  Generates the boilerplate code for defining the dispatching function for a given @c TAG

  @par Usage:

  @param NAMESPACE  Namespace containing @c TAG
  @param TAG        Tag type identifier
**/
#define BOOST_DISPATCH_FUNCTION_DECLARATION(NAMESPACE,TAG)                                          \
template<typename... Specifications> struct impl_##TAG;                                             \
template<typename Site, typename... Ts>                                                             \
BOOST_FORCEINLINE generic_dispatcher<NAMESPACE::TAG>                                                \
BOOST_DISPATCH_IMPLEMENTS ( TAG , ::boost::dispatch::unspecified_<Site> const&                      \
                                , ::boost::dispatch::unknown_<Ts> const&...                         \
                          ) BOOST_NOEXCEPT                                                          \
{                                                                                                   \
  return {};                                                                                        \
}                                                                                                   \
/**/

/*!
  @ingroup group-function

  Generates a callable object from a @c TAG

  @par Usage:

  @param TAG  Fully qualified tag type to adapt
  @param NAME Callable object identifier
**/
#define BOOST_DISPATCH_CALLABLE_DEFINITION(TAG,NAME)                                                \
static const boost::dispatch::functor<TAG> NAME = {}                                                \
/**/

/*!
  @ingroup group-function

  Generates a function from a @c TAG

  @par Usage:

  @param TAG  Fully qualified tag type to adapt
  @param NAME Function object identifier
**/
#define BOOST_DISPATCH_FUNCTION_DEFINITION(TAG,NAME)                                                \
template<typename... Args> BOOST_FORCEINLINE                                                        \
auto NAME(Args&&... args) BOOST_NOEXCEPT                                                            \
        -> decltype ( TAG::dispatch_to( boost::dispatch::default_site<TAG>()                        \
                                      , typename boost::dispatch::hierarchy_of<Args>::type()...     \
                                      )( std::forward<Args>(args)...)                               \
                    )                                                                               \
{                                                                                                   \
  return TAG::dispatch_to ( boost::dispatch::default_site<TAG>()                                    \
                          , typename boost::dispatch::hierarchy_of<Args>::type()...                 \
                          )( std::forward<Args>(args)...);                                          \
}                                                                                                   \
/**/

#endif
