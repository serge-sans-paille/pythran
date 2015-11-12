//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRANSFORM_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::transform function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct transform_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * Evaluates all elements of \c a1, possibly in parallel,
   * and store the result in \c a0.
   *
   * \param a0 Expression to store result in
   * \param a1 Expression to evaluate
   * \param a2 Optional pair containing linear offset and number of element to process
   * \return nothing
   */
  //============================================================================

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::transform_, transform, 2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1 const&), 2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0 const&)(A1&), 2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1&), 2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::transform_, transform, 3)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1 const&)(A2 const&), 3)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0 const&)(A1&)(A2 const&), 3)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::transform_, transform, (A0&)(A1&)(A2 const&), 3)
}

#endif
