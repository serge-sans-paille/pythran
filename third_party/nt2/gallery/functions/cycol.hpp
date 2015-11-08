//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CYCOL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CYCOL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_cycol cycol
 *
 * \par Description
 * cycol  Matrix whose columns repeat cyclically.
 *    a = cycol(m n, k) is an m-by-n matrix of the form
 *    a = b(_(1, m),_(1, n)) where b = cath(c, c, c...) and c = randn(m, k). thus a's
 *    columns repeat cyclically, and a has rank at most k. k need not
 *    divide n. k defaults to round(n/4).
 *
 *    note:
 *    this type of matrix can lead to underflow problems for gaussian
 *    elimination. see the reference below.
 *
 *    Reference:
 *    [1] NA Digest Volume 89, Issue 3 (January 22, 1989).
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cycol.hpp>
 * \endcode
 *
 **/
//==============================================================================
// cycol actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag cycol_ of functor cycol
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct cycol_ : ext::unspecified_<cycol_> { typedef ext::unspecified_<cycol_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cycol_, cycol, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cycol_, cycol, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cycol_, cycol, 4)

  template < class T > container::table<T> cycol(size_t m, size_t n, size_t k = 0)
  {
    return nt2::cycol(m, n, k, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::cycol_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::value(boost::proto::child_c<2>(e));
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::cycol_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type   tmp_t;
    typedef typename boost::proto::result_of::value<tmp_t>::value_type t_t;
    typedef typename t_t::type                                         type;
  };
} }
#endif

