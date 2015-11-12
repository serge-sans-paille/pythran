//==============================================================================
//         Copyright 2003 - 2011  LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011  LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_PREPROCESSOR_REMOVE_TYPENAME_HPP_INCLUDED
#define BOOST_DISPATCH_PREPROCESSOR_REMOVE_TYPENAME_HPP_INCLUDED

/*!
  @file
  @brief Defines the BOOST_DISPATCH_PP_REMOVE_TYPENAME macro
**/

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>

/// INTERNAL ONLY
/// `checking_prefix ## tokens` expand to unary (e.g., `(1)`) iff `tokens` start
/// with keyword to check.
///
/// Boost.Preprocessor author P. Mensodines confirmed on an Boost email thread
/// (subject ``check if a token is a keyword (was "BOOST_PP_IS_UNARY()")'')
/// that it is OK to used `PP_IS_UNARY()` to check if tokens match predefined
/// "keyword" as it is done by the macros below (even if `PP_IS_UNARY()` is
/// technically only part of Boost.Preprocessor private API).
#define BOOST_DISPATCH_PP_DETAILS_KEYWORD_FACILITY_IS_FRONT(T, checking_prefix) \
BOOST_PP_IS_UNARY(BOOST_PP_CAT(checking_prefix, T))                             \
/**/

/// INTERNAL ONLY
/// `is_front_macro(tokens)` is 1 iff `tokens` start with keyword to remove.
/// `removing_prefix ## <keyword-to-remove>` must expand to nothing.
#define BOOST_DISPATCH_PP_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT(               \
        tokens, is_front_macro, removing_prefix)                               \
    BOOST_PP_EXPAND( /* without EXPAND doesn't expand on MSVC */               \
        BOOST_PP_IIF(is_front_macro(tokens),                                   \
            BOOST_PP_CAT                                                       \
        ,                                                                      \
            tokens BOOST_PP_TUPLE_EAT(2)                                       \
        )(removing_prefix, tokens)                                             \
    )                                                                          \
/**/

/// INTERNAL ONLY
#define BOOST_DISPATCH_PP_DETAILS_KEYWORD_TYPENAME_IS_typename (1) /* unary */

/// INTERNAL ONLY
#define typename_BOOST_DISPATCH_PP_DETAILS_KEYWORD_TYPENAME_IS (1) /* unary */

/// INTERNAL ONLY
#define BOOST_DISPATCH_PP_DETAILS_KEYWORD_TYPENAME_REMOVE_typename /* nothing */

/// INTERNAL ONLY
#define typename_BOOST_DISPATCH_PP_DETAILS_KEYWORD_TYPENAME_REMOVE /* nothing */

/// INTERNAL ONLY
#define BOOST_DISPATCH_PP_DETAILS_KEYWORD_IS_TYPENAME_FRONT(tokens)            \
BOOST_DISPATCH_PP_DETAILS_KEYWORD_FACILITY_IS_FRONT(tokens,                    \
            BOOST_DISPATCH_PP_DETAILS_KEYWORD_TYPENAME_IS_)                    \
/**/

/*!
  @brief Remove typename from token

  For any token @c X, this macro returns the same token from which a potential
  leading @c typename keyword has been removed. If no typename keyword is present,
  this macros evaluates to @c X itself without error.

  The original implementation of this macro is from Lorenzo Caminiti.

  @param X Symbol to remove @c typename from

  @par Usage:

  @include pp_remove_typename.cpp

  This produces the following output
  @code
  add_pointer<float>::type
  add_pointer<T>::type
  @endcode

**/
#define BOOST_DISPATCH_PP_REMOVE_TYPENAME(X)                                   \
BOOST_DISPATCH_PP_DETAILS_KEYWORD_FACILITY_REMOVE_FRONT(X,                     \
        BOOST_DISPATCH_PP_DETAILS_KEYWORD_IS_TYPENAME_FRONT,                   \
        BOOST_DISPATCH_PP_DETAILS_KEYWORD_TYPENAME_REMOVE_)                    \
/**/

#endif
