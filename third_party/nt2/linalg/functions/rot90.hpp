//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_ROT90_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_ROT90_HPP_INCLUDED

#include <nt2/include/functor.hpp>

#include <nt2/include/functions/is_odd.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/value_as.hpp>

/*!
 rot90  rotate matrix 90 degrees.
    rot90(a) is the 90 degree counterclockwise rotation of matrix a.
    rot90(a,k) is the k*90 degree rotation of a, k = +-1,+-2,...

    example,
        a = [1 2 3      b = rot90(a) = [ 3 6
             4 5 6 ]                     2 5
                                         1 4 ]
**/
//==============================================================================
// rot90 actual class forward declaration
//==============================================================================

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag rot90_ of functor rot90
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct rot90_   :  ext::unspecified_<rot90_> { typedef ext::unspecified_<rot90_> parent; };
    struct rot90_0_ :  tag::formal_              { typedef tag::formal_ parent;              };

  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rot90_,   rot90, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::rot90_0_, rot90, 1)

}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<tag::rot90_, Domain, 1, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      std::swap(sizee[0], sizee[1]);
      return sizee;
    }
  };

  template<class Domain, class Expr,  int N>
  struct size_of<tag::rot90_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      int k =  boost::proto::child_c<1>(e);
      if(nt2::is_odd(k)) std::swap(sizee[0], sizee[1]);
      return sizee;
    }
  };

  template <class Domain, class Expr,  int N>
  struct value_type<tag::rot90_, Domain, N, Expr>
       : meta::value_as<Expr,0>
  {};
} }

#endif
