//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_BSEARCH_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_BSEARCH_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief bsearch generic tag

     Represents the bsearch function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct bsearch_ : ext::unspecified_<bsearch_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<bsearch_> parent;
    };
  }
  /*!
    one dimensional binary search
    \par

    @par Semantic:

    For every parameters expressions

    @code
    auto index = bsearch(xx, xi);
    @endcode

    Performs a binary search of an ordered array of increasing values.
    and returns the indices of the xi such that xi belongs to the interval
    [xx(index(i)), xx(index(i)+1)] and the implicit bracket [index(i), index(i)+1]
    always corresponds to a region within the implicit value range of
    the value array.

    Note that this means the relationship of x = xi(i) to xx(index)
    and xx(index+1) depends on the result region, i.e. the
    behaviour at the boundaries may not correspond to what you
    expect. We have the following complete specification of the
    behaviour.

    Suppose the input is xx = { x0, x1, ..., xN }
      - if ( x == x0 )           then  index == 0
      - if ( x > x0 && x <= x1 ) then  index == 0, and similarly for other interior pts
      - if ( x >= xN )           then  index == N-1

    @param a0

    @param a1

    @return a index expression
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::bsearch_, bsearch, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::bsearch_, Domain, N, Expr>
        : meta::size_as<Expr,1>
  {};

  template <class Domain, class Expr,  int N>
  struct value_type < tag::bsearch_, Domain,N,Expr>
  {
   typedef typename   boost::proto::result_of
                    ::child_c<Expr&, 1>::value_type::value_type elt_t;
   typedef typename nt2::meta::as_integer<elt_t>::type          type;
  };
} }

#endif
