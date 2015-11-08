//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_KRYLOV_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_KRYLOV_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_krylov krylov
 *
 * \par Description
 *   krylov(a,x,j) is the krylov matrix
 *    [x, a*x, a^2*x, ..., a^(j-1)*x], where a is an n-by-m matrix and
 *    x is an m-vector. the defaults are x = ones(m,1), and j = n.
 *
 *    krylov(n) is the same as krylov(randn(n)).
 *    Reference:
 *    G. H. Golub and C. F. Van Loan, Matrix Computations, third edition,
 *    Johns Hopkins University Press, Baltimore, Maryland, 1996, Sec. 7.4.5.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/krylov.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// krylov actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag krylov_ of functor krylov
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct krylov_ : ext::unspecified_<krylov_>
    {
      typedef ext::unspecified_<krylov_>  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::krylov_, krylov, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::krylov_, krylov, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::krylov_, krylov, 3)

}

namespace nt2 { namespace ext
{
 template<class Domain, class Expr,  int N>
  struct  size_of<tag::krylov_, Domain, N, Expr>
  {
    typedef _2D                                                        result_type;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename boost::dispatch::meta::is_integral<t_type>::type    choicek_t;
    typedef boost::mpl::int_<N>                                          choicen_t;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = get_m(boost::proto::child_c<0>(e), choicek_t() );
      sizee[1] = get_n(e, choicen_t());
      return sizee;
    }
  private:
    template <class A>
    BOOST_FORCEINLINE static size_t get_m(A const & a, boost::mpl::true_ const &)
    {
      return a;
    }
    template <class A>
    BOOST_FORCEINLINE static size_t get_m(A const & a, boost::mpl::false_ const &)
    {
      return nt2::size(a, 1);
    }

   BOOST_FORCEINLINE static size_t get_n(Expr const & a, boost::mpl::int_<1> const &)
    {
      return nt2::size(boost::proto::child_c<0>(a), 1);
    }

    template < class T>
    BOOST_FORCEINLINE static size_t get_n(Expr const & a, T const &)
    {
      return boost::proto::child_c<2>(a);
    }


  };

  template <class Domain, class Expr>
  struct value_type < tag::krylov_, Domain,1,Expr>
  {
    typedef double type;
  };
  template <class Domain, class Expr, int N>
  struct value_type < tag::krylov_, Domain,N,Expr>  : meta::value_as<Expr, 0>
  { };
} }


#endif
