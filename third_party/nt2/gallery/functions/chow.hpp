//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CHOW_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CHOW_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_chow chow
 *
 * \par Description
 * compute a chow matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/chow.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// chow actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag chow_ of functor chow
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct chow_ : ext::unspecified_<chow_> { typedef ext::unspecified_<chow_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chow_, chow, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chow_, chow, 2)

  template < class T > container::table<T> chow(size_t n)
  {
    return nt2::chow(n, T(1), T(0), meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct size_of<tag::chow_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  boost::proto::child_c<0>(e);
      result_type sizee;
      sizee[0] = sizee[1] = n;
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::chow_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type child0;
    typedef typename child0::value_type type;
  };

  template <class Domain, class Expr>
  struct value_type < tag::chow_, Domain,1,Expr>
  {
    typedef double type;
  };

} }
#endif

