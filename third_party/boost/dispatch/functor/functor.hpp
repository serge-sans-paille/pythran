#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_FUNCTOR_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_FUNCTOR_HPP_INCLUDED

/*!
 * \file
 * \brief Implements Boost.Dispatch main functor handler
 */

/*!
 * \defgroup functors Functor system
 * \ingroup sdk
 * This module gathers macros, classes and functions to define, implement
 * and specialize polymorphic functors.
 */

#include <boost/config.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/functor/details/call.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/attributes.hpp>

#if ((defined(BOOST_NO_VARIADIC_TEMPLATES) || defined(BOOST_NO_RVALUE_REFERENCES)) \
 && defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)) || defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/slot/slot.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#endif

namespace boost { namespace dispatch
{
  //============================================================================
  /*!
   * \ingroup functors
   * \ref functor is a generic, concept-dispatched polymorphic function object.
   * Every function in Boost.Dispatch are defined in term of implementing a call strategy
   * for \ref functor. The main rationale is to centralize and homogenize the way
   * functions with multiple possible implementation with respect to types,
   * architectures and compilation phases are handled.
   *
   * \tparam Tag Function tag to dispatch to.
   * \tparam EvalContext Tag defining how to perform said function call with
   * respect to architecture or phase settings.
   *
   * \par Models:
   * \dco
   *
   * \see call
   * \see hierarchy
   * \see make_functor
   */
  //============================================================================
  template<class Tag, class EvalContext> struct functor
  {
    typedef Tag         tag_type;
    typedef EvalContext context_type;

    template<class Sig> struct result;

    #if (   !defined(BOOST_NO_VARIADIC_TEMPLATES)               \
        &&  !defined(BOOST_NO_RVALUE_REFERENCES)                \
        &&  !defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)  \
        )                                                       \
        || defined(DOXYGEN_ONLY)
    template<class This, class... Args>
    struct result<This(Args...)>
#if !defined(DOXYGEN_ONLY)
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<Args>::type...)
                                , EvalContext
                                >::type(typename meta::as_ref<Args>::type...)
                 >
#endif
    {};

    //==========================================================================
    /*!
     * Polymorphic variadic function call operator. This catch-all operators
     * dispatches its arguments to the proper type and architecture based
     * implementation using the hierarchy_of system.
     *
     * \param args Arguments of function \c Tag implementation
     * \return The result of the calculation of function \c Tag
     */
    //==========================================================================
    template<class... Args> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<Args>::type...)>::type
    operator()( Args&& ...args ) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<Args>::type...)
                          , EvalContext
                          >::type()
             ( static_cast<typename meta::as_ref<Args>::type>(args)... );
    }
    #elif !defined(BOOST_NO_RVALUE_REFERENCES) && !defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES_NO_0X)

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/functor/preprocessed/functor0x.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/functor0x.hpp")
#undef BOOST_FORCEINLINE
#endif

    #define M4(z,n,t) typename meta::as_ref<A##n>::type
    #define M5(z,n,t) static_cast<typename meta::as_ref<A##n>::type>(a##n)

    #define BOOST_PP_ITERATION_PARAMS_1 (4, (1, BOOST_DISPATCH_MAX_ARITY, "boost/dispatch/functor/functor.hpp", 0))
    #include BOOST_PP_ITERATE()
    #undef M4
    #undef M5

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#else

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/functor/preprocessed/functor.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/functor.hpp")
#undef BOOST_FORCEINLINE
#endif

    #define M0(z,n,t) (((A##n)(&))((A##n)(const&)))
    #define M1(r,data,elem) (BOOST_PP_SEQ_ELEM(0, elem) BOOST_PP_SEQ_ELEM(1, elem))
    #define M2(r,data,i,elem) BOOST_PP_COMMA_IF(i) elem a##i
    #define M3(r,product) (BOOST_PP_SEQ_FOR_EACH(M1, ~, product))
    #define M4(z,n,t) typename meta::as_ref<A##n>::type

    #define BOOST_PP_ITERATION_PARAMS_1 (4, (1, BOOST_DISPATCH_MAX_ARITY, "boost/dispatch/functor/functor.hpp", 1))
    #include BOOST_PP_ITERATE()

    #undef M0
    #undef M1
    #undef M2
    #undef M3
    #undef M4

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

    #endif
    };
} }

#endif
#else
#if BOOST_PP_ITERATION_DEPTH() == 1
  #define BOOST_PP_VALUE BOOST_PP_ITERATION()
  #include BOOST_PP_ASSIGN_SLOT(1)
  #define n BOOST_PP_SLOT(1)

    template<class This, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(n, A))>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(BOOST_PP_ENUM(n, M4, ~))
                                , EvalContext
                                >::type(BOOST_PP_ENUM(n, M4, ~))
                 >
    {
    };

  #if BOOST_PP_ITERATION_FLAGS() == 1
    #define PERM_SEQ BOOST_PP_SEQ_FOR_EACH_PRODUCT(M3, BOOST_PP_REPEAT(n, M0, ~))
    #define BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_PP_SEQ_SIZE(PERM_SEQ)-1, "boost/dispatch/functor/functor.hpp"))
    #include BOOST_PP_ITERATE()
    #undef PERM_SEQ
  #else

    template<BOOST_PP_ENUM_PARAMS(n, class A)> BOOST_FORCEINLINE
    typename result<functor(BOOST_PP_ENUM(n, M4, ~))>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, && a)) const
    {
      return typename meta::
             dispatch_call< Tag(BOOST_PP_ENUM(n, M4, ~))
                          , EvalContext
                          >::type()
            (BOOST_PP_ENUM(n, M5, ~));
    }

  #endif
  #undef n

#elif BOOST_PP_ITERATION_DEPTH() == 2

  #define SEQ BOOST_PP_SEQ_ELEM(BOOST_PP_ITERATION(), PERM_SEQ)

    template<BOOST_PP_ENUM_PARAMS(n, class A)> BOOST_FORCEINLINE
    typename result<functor(BOOST_PP_SEQ_ENUM(SEQ))>::type
    operator()(BOOST_PP_SEQ_FOR_EACH_I(M2, ~, SEQ)) const
    {
      return typename meta::
             dispatch_call< Tag(BOOST_PP_SEQ_ENUM(SEQ))
                          , EvalContext
                          >::type()
            (BOOST_PP_ENUM_PARAMS(n, a));
    }

  #undef SEQ

#endif
#endif
