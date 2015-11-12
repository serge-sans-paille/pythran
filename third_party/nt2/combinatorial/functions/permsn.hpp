//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_PERMSN_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_PERMSN_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief permsn generic tag

     Represents the permsn function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct permsn_ : ext::unspecified_<permsn_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<permsn_> parent;
    };
  }
  /*!
    Computes permutations enumeration

    @par Semantic:

    For every n and k

    @code
    auto r = permsn(n, k);
    @endcode

    is similar to:

    @code
    auto r = perms(_(1, n), k);
    @endcode

    @see @funcref{perms}, @funcref{colon}
    @param a0
    @param a1
    Return the k first or, by default, the n! permutations of [1 ... n]
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::permsn_, permsn, 2)
  /// overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::permsn_, permsn, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::permsn_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = boost::proto::child_c<0>(e);

      std::size_t l = 1;
      for(std::size_t i=2;i<=sizee[0];++i) l *= i;

      sizee[1] = nt2::min(boost::proto::child_c<1>(e), l);

      return sizee;
    }
  };


  /// INTERNAL ONLY
  template <class Domain, class Expr, int N>
  struct value_type < tag::permsn_, Domain,N,Expr>
  {
    typedef std::size_t type;
  };
} }

#endif
