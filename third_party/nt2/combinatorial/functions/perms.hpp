//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_PERMS_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_PERMS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief perms generic tag

     Represents the perms function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct perms_ : ext::unspecified_<perms_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<perms_> parent;
    };
  }
  /*!
    Computes permutations

    @par Semantic:

    For every table expression

    @code
    auto r = perms(v, k);
    @endcode

    returns the first k permutations
    of the v elements. k defaults to !numel(v)

    Take care in this last case that numel(v) <= 10 to avoid
    exhausting memory

    @param a0
    @param a1

    @see @funcref{permsn}, @funcref{numel}, @funcref{combs}
    @return an expression which eventually will evaluate to the result
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::perms_, perms, 2)
  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::perms_, perms, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::perms_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = nt2::numel(boost::proto::child_c<0>(e));

      std::size_t l = 1;
      for(std::size_t i=2;i<=sizee[0];++i) l *= i;

      sizee[1] = nt2::min(boost::proto::child_c<1>(e), l);

      return sizee;
    }
  };

  /// INTERNAL ONLY
  template <class Domain, class Expr, int N>
  struct value_type < tag::perms_, Domain,N,Expr>
    : meta::value_as<Expr,0>
  { };
} }

#endif
