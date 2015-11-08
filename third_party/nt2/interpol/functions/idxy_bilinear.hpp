//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_IDXY_BILINEAR_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_IDXY_BILINEAR_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief idxy_bilinear generic tag

     Represents the idxy_bilinear function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct idxy_bilinear_ : ext::unspecified_<idxy_bilinear_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<idxy_bilinear_> parent;
    };
  }
  /*!
    Performs two dimensional idxy_bilinear interpolation given an
    array a and two vector idx and idy of "real" indices provides the
    interpolated values along the two chosen array dimensions by
    bilinear formula.

    @par Semantic:

    calls can be of the forms:

      - idxy_bilinear(a0, idx, idy)
      - idxy_bilinear(a0, idx, idy, true) allowing extrapolation
      - idxy_bilinear(a0, idx, idy, val1) putting val1 outside the bounds
      - idxy_bilinear(a0, idx, idy, val1, val2)}, putting val1 under the index bounds val2 over
      - idxy_bilinear(a0, idx, idy, val1x val2x, val1y, val2y)
      - idxy_bilinear(a0, idx, idy, _, dim1, dim2) are the dimensions of interpolation 2 (rows), 1 (columns) of a0 by default
      - idxy_bilinear(a0, idx, idy, val1, dim1, dim2)
      - idxy_bilinear(a0, idx, idy, val1, val2, dim1, dim2)
      - idxy_bilinear(a0, idx, idy, val1x val2x, val1y, val2y, dim1, dim2) can also be used

      typically if a is a matrix, idx is a value situated between i and i+1 and
      idy is a value situated between j and j+1 the result is:
      @code
      (a(i, j)*(idx-i)+a(i+1, j)*(i+1-idx))*(jdx-j)+
      (a(i, j+1)*(idx-i)+a(i+1, j+1)*(i+1-idx))*(j+1-jdx)
      @endcode

    @param a0
    @param a1
    @param a2
    @param a3
    @param a4
    @param a5
    @param a6
    @param a7
    @param a8
    @param a9

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 10)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 4)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 6)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 7)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 9)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct size_of<tag::idxy_bilinear_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,N-2>::type   choice1_t;
    typedef typename boost::proto::result_of::child_c<Expr&,N-1>::type   choice2_t;

    typedef typename  boost::proto::result_of
                      ::child_c<Expr&, 1>::value_type::extent_type  result_type;

    result_type operator()(Expr& e) const
    {
      const choice1_t & v1   =  boost::proto::child_c<N-2>(e);
      const choice2_t & v2   =  boost::proto::child_c<N-1>(e);
      typedef typename nt2::meta::is_integral<choice1_t>::type c_t;
      std::size_t dim1 = 2, dim2 = 1;
      getdims(boost::proto::child_c<1>(e), v1, v2, dim1, dim2, c_t());
      result_type sizee = boost::proto::child_c<0>(e).extent();
      sizee[dim1-1] = numel(boost::proto::child_c<1>(e));
      sizee[dim2-1] = numel(boost::proto::child_c<2>(e));
      return sizee;
    }

    template<class X, class C1, class C2> static
    void getdims( const X &, const C1 &, const C2 &
                , std::size_t&, std::size_t&, const boost::mpl::false_&
                )
    {}

    template<class X, class C1, class C2> static
    void getdims( const X &, const C1& v1, const C2& v2
                , std::size_t& dim1, std::size_t& dim2, const boost::mpl::true_&
                )
    {
      dim1 = v1;
      dim2 = v2;
    }
  };

  template <class Domain, class Expr,  int N>
  struct  value_type < tag::idxy_bilinear_, Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
