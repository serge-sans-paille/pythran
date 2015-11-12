//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_INVHILB_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_INVHILB_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_invhilb invhilb
 *
 * \par Description
 *   invhilb(n) is the inverse of the n by n matrix with elements
 *   1/(i+j-1), which is a famous example of a badly conditioned
 *   matrix.  the result is exact for  n  less than about 15.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/invhilb.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag invhilb_ of functor invhilb
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct invhilb_ : ext::unspecified_<invhilb_>
    {
      typedef ext::unspecified_<invhilb_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::invhilb_, invhilb, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::invhilb_, invhilb, 2)

  template<typename T, typename A0>
  typename  boost::dispatch
          ::meta::call<tag::invhilb_( A0 const&, meta::as_<T> const&)>::type
  invhilb(A0 const& n)
  {
    return nt2::invhilb(n, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::invhilb_, Domain, N, Expr>
        : meta::boxed_size<Expr,1>
  {};

  template <class Domain, class Expr,  int N>
  struct value_type < tag::invhilb_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename boost::proto::result_of::value<c0_t>::value_type       v_t;
    typedef typename v_t::type                                             type;
  };
} }

#endif
