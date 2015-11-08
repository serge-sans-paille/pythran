//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FLIPLR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FLIPLR_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief fliplr generic tag

     Represents the fliplr function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fliplr_ : ext::elementwise_<fliplr_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fliplr_> parent;
    };
  }
  /*!
    Flips an expression around the vertical axis
    @par Semantic:

    For every table expression

    @code
    auto r = fliplr(a0);
    @endcode

    is similar to:

    @code
    auto r = a0(_(height(a0), -1, 1), ..., _);
    @endcode

    @see @funcref{height}, @funcref{colon}
    @param a0

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::fliplr_       , fliplr, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N,class Expr>
  struct  size_of<nt2::tag::fliplr_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
