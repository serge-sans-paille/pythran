//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_ORTH_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_ORTH_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * @brief orth basis of image space
 *    q = orth(a) is an orthonormal basis for the range of a.
 *    that is, transconj(q)*q = i, the columns of q span the same space as
 *    the columns of a, and the number of columns of q is the
 *    rank of a.
 *    q = orth(a, tol) produces an image space basis of a compatible with the
 *    kernel basis given by null(a, tol)
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag orth_ of functor orth
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct orth_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orth_, orth, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orth_, orth, 2)

}

#endif
