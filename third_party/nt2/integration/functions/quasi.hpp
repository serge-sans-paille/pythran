//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_QUASI_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_QUASI_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief quasi generic tag

     Represents the quasi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct quasi_ : ext::unspecified_<quasi_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<quasi_> parent;
    };
  }
  /*!
    uniform quasi random numbers generator used by qmtc

    @par Semantic:

    For every integers n,  m and floating type T0

    @code
    auto r = quasi(n, m, as_<T>());
    @endcode

    produces a table of quasi-random number of size nxm of
    elements of type T0 in the interval [0, 1[

    @see @funcref{qmtc}
    @param a0
    @param a1
    @param a2

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::quasi_, quasi, 3)
 }

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
   template<class Domain, class Expr,  int N>
  struct  size_of<tag::quasi_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      size_t n = boost::proto::value(boost::proto::child_c<1>(e));
      size_t m = boost::proto::value(boost::proto::child_c<0>(e));
      sizee[1] = n;
      sizee[0] = m;
      return sizee;
    }
  };

  /// INTERNAL ONLY
   template <class Domain, class Expr, int N>
  struct value_type < tag::quasi_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,2>::type  t_t;
    typedef typename  boost::dispatch::meta::semantic_of<t_t>::type   type;
  };
} }
#endif

