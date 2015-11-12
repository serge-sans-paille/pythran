//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_CONCEPTS_HPP_INCLUDED
#define NT2_SDK_ERROR_CONCEPTS_HPP_INCLUDED

/*!
 * @file
 * @brief Defines macros controlling the handling of Concepts checks
 */

#include <boost/concept_check.hpp>

#if defined(DOXYGEN_ONLY)
/**
* @brief Concept-based compile-time assertion
*
* This macro, used at any scope, verify that the concept checking template
* specialization \c CONCEPT is satisfied.
**/
#define NT2_CONCEPT_ASSERT(CONCEPT)

/**
* @brief Concept-based compile-time function requirement
*
* This macro, that can be used as a function return type, checks that all the
* concept checking templates in the @c CONCEPTS preprocessor list are satisifed.
* If they are, the function is allowed to be defined with a return type equals
* to @c TYPE.
**/
#define NT2_CONCEPT_REQUIRE(CONCEPTS,TYPE)
#endif

#if !defined(DOXYGEN_ONLY)

#if defined(NT2_USE_CONCEPTS)
#define NT2_CONCEPT_ASSERT(CONCEPT)         BOOST_CONCEPT_ASSERT(CONCEPT)
#define NT2_CONCEPT_REQUIRE(CONCEPTS,TYPE)  BOOST_CONCEPT_REQUIRE(CONCEPT,TYPE)
#else
#define NT2_CONCEPT_ASSERT(CONCEPT)
#define NT2_CONCEPT_REQUIRE(CONCEPTS,TYPE)
#endif

#endif

#endif
