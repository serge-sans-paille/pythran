//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_IDX_LINEAR_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_IDX_LINEAR_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief idx_linear generic tag

     Represents the idx_linear function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct idx_linear_ : ext::unspecified_<idx_linear_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<idx_linear_> parent;
    };
  }
  /*!
    one dimensional linear interpolation along a dimension

    given an ordered array a of increasing values and a vector idx of
    "real" indices provides the interpolated values along the a chosen
    direction in the array by linear formula.

    @par Semantic:

    calls can be of the forms:

      - idx_linear(a, idx)
      - idx_linear(a, idx, true) allowing extrapolation
      - idx_linear(a, idx, val1) putting val1 outside the bounds
      - idx_linear(a, idx, val1, val2)}, putting val1 under the index bounds val2 over
      - idx_linear(a, idx, _, dim) dim is the dimension of interpolation (firstnonsingleton of xi by default)
      - idx_linear(a, idx, val1, dim)
      - idx_linear(a, idx, val1, val2, dim)

      typically if a is a vector and  x is a value situated between i and i+1 the result is
      @code
      a(i)*(x-i)+a(i+1)*(i+1-x)
      @endcode

    @param a0
    @param a1
    @param a2
    @param a3
    @param a4

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 4)

}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct size_of<tag::idx_linear_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr,N-1>::value_type v_t;
    typedef typename nt2::meta::is_integral<v_t>::type                      c_t;

    typedef typename  boost::proto::result_of
                      ::child_c<Expr&,0>::value_type::extent_type   result_type;

    result_type operator()(Expr& e) const
    {
      std::size_t dim = nt2::firstnonsingleton(boost::proto::child_c<1>(e));
      result_type sizee = boost::proto::child_c<0>(e).extent();
      sizee[dim-1] = numel(boost::proto::child_c<1>(e));
      return sizee;
    }
  };

  template <class Domain, class Expr,  int N>
  struct  value_type < tag::idx_linear_, Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
