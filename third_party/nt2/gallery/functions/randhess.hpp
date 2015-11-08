//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_RANDHESS_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_RANDHESS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_randhess randhess
 *
 *    h =randhess<T>(n) returns an n-by-n real, random,
 *    orthogonal upper hessenberg matrix with elements of type T.
 *
 *    h = randhess(x), where x is an arbitrary real n-element
 *    vector (n > 1), constructs h non-randomly using the elements of x
 *    as parameters.
 *
 *    in both cases, h is constructed via a product of n-1 givens rotations.

 *    note:
 *    see [1] for representing an n-by-n (complex) unitary hessenberg
 *    matrix with positive subdiagonal elements in terms of 2n-1 real
 *    parameters (the schur parametrization). this implementation handles
 *    the real case only and is intended simply as a convenient way to
 *    generate random or non-random orthogonal hessenberg matrices.
 *
 *    Reference:
 *    [1] W. B. Gragg, The QR algorithm for unitary Hessenberg matrices,
 *        J. Comp. Appl. Math., 16 (1986), pp. 1-8.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/randhess.hpp>
 * \endcode
 *
 **/
//==============================================================================
// randhess actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag randhess_ of functor randhess
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct randhess0_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
     struct randhess_ : ext::unspecified_<randhess_>
    {
      typedef ext::unspecified_<randhess_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::randhess0_, randhess, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::randhess_, randhess, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::randhess_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = nt2::numel(boost::proto::child_c<0>(e));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::randhess_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
} }

#endif

