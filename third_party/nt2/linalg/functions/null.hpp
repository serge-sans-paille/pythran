//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_NULL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_NULL_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Define the tag null_ of functor null
    struct null_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

/*!
  @brief null:  null space of a matrix expression.

  Computes an orthonormal basis for the null space of a obtained
  from the singular value decomposition with a given tolerance.

  @param a0 Matrix to computes null space for
  @param a1 Tolerance on belonging to the null space. By default, it's
            equal to length(a)*Eps*w, with w being the largest singular
            value of a
**/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::null_, null, 2)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::null_, null, 1)

}

#endif
