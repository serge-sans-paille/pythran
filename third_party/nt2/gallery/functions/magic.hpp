//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_MAGIC_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_MAGIC_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_magic magic
 *
 * \par Description
 *   magic(n) is an n-by-n matrix constructed from the integers
 *   1 through n^2 with equal row, column, and diagonal sums.
 *   produces valid magic squares for all n > 0 except n = 2.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/magic.hpp>
 * \endcode
 *
 *
 *
**/
//==============================================================================
// magic actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag magic_ of functor magic
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct magic_ : ext::unspecified_<magic_> { typedef ext::unspecified_<magic_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::magic_, magic, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::magic_, magic, 2)
  template < class T> container::table<T> magic(size_t n)
  {
    return nt2::magic(n, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::magic_, Domain, N, Expr>
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

  template <class Domain, class Expr,  int N>
  struct value_type < tag::magic_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  boost::dispatch::meta::semantic_of<tmp1_type>::type tmp2_type;
    typedef typename  tmp2_type::type                                          type;
  };
} }
#endif

