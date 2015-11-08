//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLVECT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLVECT_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>
#include <nt2/core/container/dsl/details/resize.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief colvect generic tag

     Represents the colvect function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct colvect_ : ext::reshaping_<colvect_>
    {
      /// @brief Parent hierarchy
      typedef ext::reshaping_<colvect_> parent;
    };
  }
  /*!
    Reshapes an expression into a column shaped table.

    @par Semantic:

    For every table expression

    @code
    auto r = colvect(a0);
    @endcode

    is similar to:

    @code
    auto r = resize(a0, numel(a0), 1);
    @endcode

    @see @funcref{rowvect}, @funcref{resize}, @funcref{numel}

    @param a0
    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::colvect_       , colvect, 1)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::colvect_  , colvect, 1)
}

namespace nt2 { namespace ext
{
  //============================================================================
  // resize colvect expression - do nothing
  //============================================================================
  template<class Domain, int N, class Expr>
  struct resize<nt2::tag::colvect_, Domain, N, Expr>
  {
    template<class Sz> BOOST_FORCEINLINE void operator()(Expr&, Sz const&) {}
  };
} }

#endif
