//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LDL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LDL_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/linalg/functions/details/ldl.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct ldl_ : ext::unspecified_<factorization::ldl_>
      {
        typedef ext::unspecified_<factorization::ldl_> parent;
      };
    }

    struct ldl_ : ext::tieable_<ldl_>
    {
      typedef ext::tieable_<ldl_>  parent;
    };
  }

  /**
   * @brief Perform LDL factorization
   *
   * For any given matrix expression, performs a LDL factorization of
   * said matrix using the specified output layout for the LDL method.
   *
   * Contrary to the nt2::factorization::ldl function which performs a partial evaldlation of
   * said decomposition, nt2::ldl returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::ldl_, ldl, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::ldl_, ldl, 2)

  namespace factorization
  {
    /**
     * @brief Initialize a LDL factorization
     *
     * For any given matrix expression, initialize a LDL factorization of
     * said matrix using the specified output layout for the LDL method
     * and return a precomputed factorization object.
     *
     * Contrary to the ldl function which performs such a factorization and
     * return a Matlab like output, factorization::ldl returns an object
     * containing the initial evaldlation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if ldl should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * LDL factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::ldl_, ldl, 1)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::ldl_, ldl, 2)
   }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::ldl_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::ldl_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
