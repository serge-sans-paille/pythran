//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_INTERP1_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_INTERP1_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief interp1 generic tag

     Represents the interp1 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct interp1_ : ext::unspecified_<interp1_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<interp1_> parent;
    };
  }
  /*!
    Returns one dimensional interpolation

    @par Semantic:

    @code
    vq = interp1(x,v,xq)
    @endcode

    interpolates to find vq, the values of the
    underlying function v=f(x) at the query points xq. x must
    be a vector of length n.

      - if v is a vector, then it must also have length n, and vq is the
      same size as xq.  if v is an array of size [n,d1,d2,...,dk], then
      the interpolation is performed for each d1-by-d2-by-...-dk value
      in v(i,_,_,...,_:).
      - if xq is a vector of length m, then vq has size [m,d1,d2,...,dk].
      - if xq is an array of size [m1,m2,...,mj], then vq is of size
      [m1,m2,...,mj,d1,d2,...,dk].

    @code
    vq = interp1(v,xq)
    @endcode

    assumes x = _(1, n), where n is length(v)
    for vector v or size(v,1) for array v.

    interpolation is the same operation as "table lookup".  described in
    "table lookup" terms, the "table" is [x,v] and interp1 "looks-up"
    the elements of xq in x, and, based upon their location, returns
    values vq interpolated within the elements of v.

    @code
    vq = interp1(x,v,xq,method)
    @endcode

    specifies alternate methods.  the default is linear
    interpolation. use _ to specify the default.

    Available methods are:

       - 'n' nearest neighbor interpolation
       - 'l' linear interpolation
       - 's' piecewise cubic spline interpolation (spline)
       - 'p' shape-preserving piecewise cubic interpolation

    @code
    vq = interp1(x,v,xq,method,true)
    @endcode

    uses the interpolation algorithm specified by method to perform
    extrapolation for elements of xq outside the interval spanned by
    x.

    @code
    vq = interp1(x,v,xq,method,extrapval)
    @endcode

    replaces the values outside of the
    interval spanned by x with extrapval.  nan and 0 are often used for
    extrapval.  The default extrapolation behavior with four input arguments
    is 'extrap' for 's' and 'p' and extrapval = nan (nan +i*nan for
    complex values) for the other methods.

    @param a0
    @param a1
    @param a2
    @param a3
    @param a4

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::interp1_, interp1, 4)
}

namespace nt2 { namespace ext
{
  ///INTERNAL ONLY
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::interp1_, Domain, N, Expr>
        : meta::size_as<Expr,2>
  {};

  ///INTERNAL ONLY
  template <class Domain, class Expr,  int N>
  struct value_type < tag::interp1_, Domain,N,Expr>
    : meta::value_as<Expr,1>
  {};
} }

#endif
