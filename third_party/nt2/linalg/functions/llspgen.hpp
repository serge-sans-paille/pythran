//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LLSPGEN_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LLSPGEN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct llspgen_ : ext::tieable_<llspgen_>
    {
      typedef ext::tieable_<llspgen_>  parent;
    };
  }

  /**
   * @brief Generate LLSP min(Ax-b) such that cond(A) = n^q and residual norm = nr
   *
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::llspgen_, llspgen, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::llspgen_, llspgen, 5)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::llspgen_,Domain,N,Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type( boost::proto::value( boost::proto::child_c<0>(e) )
                        , boost::proto::value( boost::proto::child_c<1>(e) )
                        );
    }
  };

  template<class Domain, class Expr>
  struct  value_type<tag::llspgen_,Domain,4,Expr>
  {
    typedef double type;
  };

  template<class Domain, class Expr>
  struct  value_type<tag::llspgen_,Domain,5,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,4>::value_type child0;
    typedef typename child0::value_type type;
  };
} }

#endif
