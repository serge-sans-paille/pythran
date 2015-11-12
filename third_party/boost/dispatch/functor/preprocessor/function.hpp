//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED

/*!
  @file
  @brief Defines macro boilerplate for writing dispatchable functions
**/

#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/meta/result_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/cat.hpp>

#if !defined(DOXYGEN_ONLY)
#define BOOST_DISPATCH_FUNCTION_RETURN_TYPE(Tag,Args)                          \
typename boost::dispatch::meta::result_of< typename boost::dispatch::meta::    \
  dispatch_call< Tag( BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Args)                   \
                                   , BOOST_DISPATCH_FN_ARGS                    \
                                   , Args                                      \
                                   )                                           \
                    )                                                          \
               >::type                                                         \
  ( BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Args), BOOST_DISPATCH_FN_ARGS, Args) )     \
>::type                                                                        \
/**/
#else
#define BOOST_DISPATCH_FUNCTION_RETURN_TYPE(Tag,Args) details::unspecified     \
/**/
#endif

/*!
  @brief Generate dispatch-based function prototype

  Given a @c Tag, generate the prototype for a function called @c Name taking
  @c N parameters and using boost::dispatch  for its implementation.

  @param Tag  Function Tag to implement
  @param Name Function public name
  @param N    Number of parameters

  @par Usage:

  @code
  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::plus_, addition, 2);
  @endcode

  Such a call will generate a code similar to :

  @code
  template<class A0, class A1>
  typename boost::dispatch::meta::call<tag::plus_(A0 const&, A1 const&)>::type
  addition(A0 const& a0, A1 const& a1 );
  @endcode
**/
#define BOOST_DISPATCH_FUNCTION_INTERFACE(Tag, Name, N)                        \
template<BOOST_PP_ENUM_PARAMS(N,class A)>                                      \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::result_of< typename boost::dispatch::meta::    \
  dispatch_call< Tag( BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a) )            \
              >::type                                                          \
  ( BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a) )                              \
>::type                                                                        \
Name( BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a) )                            \
/**/

/*!
  @brief Generate dispatch-based function body

  Given a @c Tag, generate the body of a function taking @c N parameters and
  using boost::dispatch  for its implementation.

  @param Tag  Function Tag to implement
  @param N    Number of parameters

  @par Usage:

  @code
  BOOST_DISPATCH_FUNCTION_BODY(tag::plus_, 2);
  @endcode

  Such a call will generate a code similar to :

  @code
  return typename boost::dispatch::make_functor<tag::plus_, A0>::type()(a0,a1);
  @endcode
**/
#define BOOST_DISPATCH_FUNCTION_BODY(Tag, N)                                   \
return typename boost::dispatch::meta::                                        \
       dispatch_call< Tag( BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a) )       \
                     >::type()                                                 \
(BOOST_PP_ENUM_PARAMS(N, a));                                                  \
/**/

/*!
  @brief Generate dispatch-based function implementation

  Given a @c Tag, generate a function called @c Name taking @c N parameters and
  using boost::dispatch  for its implementation.

  @param Tag  Function Tag to implement
  @param Name Function public name
  @param N    Number of parameters

  @par Usage:

  @code
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::plus_, addition, 2);
  @endcode

  Such a call will generate a code similar to :

  @code
  template<class A0, class A1>
  typename boost::dispatch::meta::call<tag::plus_(A0 const&, A1 const&)>::type
  addition(A0 const& a0, A1 const& a1 )
  {
    return typename boost::dispatch::make_functor<tag::plus_, A0>::type()(a0,a1);
  }
  @endcode

  Note the usage of make_functor which ensure that the functor type generated
  from the tag is properly made dependent of the type parameters of the template
  function.

  @see BOOST_DISPATCH_FUNCTION_INTERFACE
  @see BOOST_DISPATCH_FUNCTION_BODY
**/
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(Tag, Name, N)                   \
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(                                    \
  Tag, Name                                                                    \
, BOOST_PP_REPEAT(N, BOOST_DISPATCH_FN_ARGS_TYPES, ~)                          \
, N                                                                            \
)                                                                              \
/**/

/// INTERNAL ONLY
#define BOOST_DISPATCH_FN_ARGS_TYPES(z,n,t) (A##n const&)

/// INTERNAL ONLY
#define BOOST_DISPATCH_FN_ARGS(z,n,t) BOOST_PP_SEQ_ELEM(n,t) a##n

/*!
  @brief Generate custom dispatch-based function implementation

  Given a @c Tag, generate a function called @c Name taking @c N parameters and
  using boost::dispatch  for its implementation. As an additional parameter,
  the exact cref qualification of each parameters is specified

  @param Args Actual parameters cref qualifications
  @param Tag  Function Tag to implement
  @param Name Function public name
  @param N    Number of parameters

  @par Usage:

  @code
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::remquo_, remquo, 3, (A0 const&)(A1&)(A2&));
  @endcode

  Such a call will generate a code similar to :

  @code
  template<class A0, class A1, class A2>
  typename boost::dispatch::meta::call<tag::remquo_(A0 const&, A1&, A2&)>::type
  remquo(A0 const& a0, A1& a1 , A2& a2 )
  {
    return typename boost::dispatch::make_functor<tag::remquo_, A0>::type()(a0,a1,a2);
  }
  @endcode

  Note the usage of make_functor which ensure that the functor type generated
  from the tag is properly made dependent of the type parameters of the template
  function.

  @see BOOST_DISPATCH_FUNCTION_IMPLEMENTATION
  @see BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF
**/
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(Tag, Name, Args, N)         \
template<BOOST_PP_ENUM_PARAMS(N, class A)>                                     \
BOOST_FORCEINLINE                                                              \
BOOST_DISPATCH_FUNCTION_RETURN_TYPE(Tag,Args)                                  \
Name( BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Args), BOOST_DISPATCH_FN_ARGS, Args) )   \
{                                                                              \
  return typename boost::dispatch::meta::                                      \
         dispatch_call< Tag( BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Args)            \
                                          , BOOST_DISPATCH_FN_ARGS             \
                                          , Args                               \
                                          )                                    \
                           )                                                   \
                      >::type()                                                \
  (BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Args), a));                          \
}                                                                              \
/**/

/// INTERNAL ONLY
#define BOOST_DISPATCH_FN_REF(z,n,t) (BOOST_PP_CAT(A,BOOST_PP_INC(n)) const&)

/*!
  @brief Generate custom dispatch-based function implementation

  Given a @c Tag, generate a function called @c Name taking @c N parameters and
  using boost::dispatch  for its implementation. The generated function is made
  so it takes its first parameters by non-const refernce

  @param Tag  Function Tag to implement
  @param Name Function public name
  @param N    Number of parameters

  @par Usage:

  @code
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(tag::store_, store, 2);
  @endcode

  Such a call will generate a code similar to :

  @code
  template<class A0, class A1>
  typename boost::dispatch::meta::call<tag::store_(A0&, A1 const&)>::type
  aligned_storeA0& a0, A1 const& a1)
  {
    return typename boost::dispatch::make_functor<tag::store_, A0>::type()(a0,a1,a2);
  }
  @endcode

  Note the usage of make_functor which ensure that the functor type generated
  from the tag is properly made dependent of the type parameters of the template
  function.

  @see BOOST_DISPATCH_FUNCTION_IMPLEMENTATION
  @see BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL
**/
// Generate a complete function implementation for self modifying operator
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(Tag, Name, N)              \
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(Tag, Name,                          \
  (A0&)BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_DISPATCH_FN_REF, ~), N)          \
/**/

#endif
