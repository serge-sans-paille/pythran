//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_OPERATORS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_OPERATORS_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/dispatch/meta/sfinae_enable_if.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/proto_fwd.hpp>

#define BOOST_SIMD_OVERLOAD_UNARY_OP(Tag, Op)                                  \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::                                               \
sfinae_enable_if< is_value<A0>                                                 \
                , dispatch::meta::                                             \
                  call< Tag(A0 const&) >                                       \
                >::type                                                        \
operator Op                                                                    \
(                                                                              \
  A0 const & a0                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0);                 \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_UNARY_OP_INC(Tag, TagInc, Op)                      \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< is_value<A0>                                                        \
         , A0&                                                                 \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0                                                                      \
)                                                                              \
{                                                                              \
  return a0 = typename dispatch::make_functor<TagInc, A0>::type()(a0);         \
}                                                                              \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< is_value<A0>                                                        \
         , A0                                                                  \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0,                                                                     \
  int                                                                          \
)                                                                              \
{                                                                              \
  A0 const that = a0;                                                          \
  operator Op(a0);                                                             \
  return that;                                                                 \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                 \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::                                               \
sfinae_enable_if< mpl::and_< is_value<A0>, is_value<A1> >                      \
                , dispatch::meta::                                             \
                  call<Tag(A0 const&, A1 const&)>                              \
                >::type                                                        \
operator Op                                                                    \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0, a1);             \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN(Tag, Op)                          \
BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                         \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< mpl::and_< is_value<A0>, is_value<A1> >                             \
         , A0&                                                                 \
         >::type                                                               \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  A0       & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  a0 = operator Op(a0, a1);                                                    \
  return a0;                                                                   \
}                                                                              \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< mpl::and_< is_value<A0>, is_value<A1> >                             \
         , A0 const&                                                           \
         >::type                                                               \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  a0 = operator Op(a0, a1);                                                    \
  return a0;                                                                   \
}                                                                              \
/**/

namespace boost { namespace simd
{
  template<class T>
  struct is_value
   : mpl::or_< boost::dispatch::details::is_mpl_integral<T>
             , boost::is_fundamental<T>
             , meta::is_native<T>
             , proto::is_expr<T>
             >
  {
  };

  namespace tag
  {
    struct inc_;
    struct dec_;
  }

  // unary operators
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::unary_plus  ,  + )
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::negate      ,  - )
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::complement  ,  ~ )
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::logical_not ,  ! )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( boost::proto::tag::plus    , boost::simd::tag::inc_, ++ )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( boost::proto::tag::minus   , boost::simd::tag::dec_, -- )

  // binary operators
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::bitwise_and , &  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::bitwise_or  , |  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::bitwise_xor , ^  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::plus        , +  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::minus       , -  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::divides     , /  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::multiplies  , *  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::modulus     , %  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::shift_left  , << )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( boost::proto::tag::shift_right , >> )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::logical_and        , && )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::logical_or         , || )

  // comparison operators
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::equal_to        , == )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::not_equal_to    , != )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::less            , <  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::greater         , >  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::less_equal      , <= )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::greater_equal   , >= )
} }

#undef BOOST_SIMD_OVERLOAD_UNARY_OP
#undef BOOST_SIMD_OVERLOAD_UNARY_OP_INC
#undef BOOST_SIMD_OVERLOAD_BINARY_OP
#undef BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN

#endif
