//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_RREF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_RREF_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_rref rref
 *
 * \par Description
 * reduced echelon
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/rref.hpp>
 * \endcode
 *
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag rref_ of functor rref
     *        in namespace nt2::tag for toolbox algebra
    **/
    namespace factorization
    {
      struct rref_ : ext::unspecified_<factorization::rref_>
      {
        typedef ext::unspecified_<factorization::rref_> parent;
      };
    }

    struct rref_ :  ext::tieable_<rref_>
    {
      typedef ext::tieable_<rref_>  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::rref_, rref, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::rref_, rref, 2)
  namespace factorization
  {
    /**
     * @brief Initialize a rref factorization
     *
     * For any given matrix expression, initialize a rref factorization of
     * said matrix using the specified output layout for the rref method
     * and return a precomputed factorization object.
     *
     * Contrary to the rref function which performs such a factorization and
     * return a Matlab like output, factorization::rref returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     *
     * @return A unspecified type containing the precomputed elements of the
     * rref factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::rref_, rref, 1)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::rref_, rref, 2)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::rref_, rref, 3)
  }

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::rref_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::rref_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
