//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_FIBONACCI_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_FIBONACCI_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fibonacci generic tag

     Represents the fibonacci function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fibonacci_ : ext::unspecified_<fibonacci_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<fibonacci_> parent;
    };
  }
  /*!
    returns the values selected by n of a fibonacci sequence starting by a and b
    the values are computed by the Binet formula and rounded if a and b are flint.

    @par Semantic:

    For every floating expressions a and b and integer expression n

    @code
    auto r = fibonacci(a, b, n);
    @endcode

    The recurrence formula defining the fibonacci sequence is:

      - r(1) = a
      - r(2) = b
      - r(i+2) = r(i+1)+r(i),  i > 2

    @param a0
    @param a1
    @param a2

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fibonacci_,fibonacci, 3)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::fibonacci_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee =  nt2::extent(boost::proto::child_c<2>(e));
      return sizee;
    }
  };

  /// INTERNAL ONLY
   template <class Domain, class Expr, int N>
  struct value_type < tag::fibonacci_, Domain,N,Expr>
    : meta::value_as<Expr,2>
  { };
} }

#endif

