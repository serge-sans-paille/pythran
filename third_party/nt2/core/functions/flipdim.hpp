//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FLIPDIM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FLIPDIM_HPP_INCLUDED


#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief flipdim generic tag

     Represents the flipdim function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct flipdim_ : ext::elementwise_<flipdim_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<flipdim_> parent;
    };
  }
  /*!
    Flips an expression around an arbitrary dimension axis

    @par Semantic:

    For every table expression a0 and integer n

    @code
    auto r = flipdim(a0{, n});
    @endcode

    is similar to:

    @code
    ri = _(size(a0, n), -1, 1);
    auto r = a0(_, ..., ri, ..., _); // ri in the n-th slot of a0
    @endcode

    n default to @c firstnonsingleton(a0).

    @see @funcref{size}, @funcref{colon}
    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::flipdim_       , flipdim, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::flipdim_       , flipdim, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::flipdim_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
