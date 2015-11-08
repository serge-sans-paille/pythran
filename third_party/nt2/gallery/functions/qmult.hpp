//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_QMULT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_QMULT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_qmult qmult
 *
 * qmult pre-multiply matrix by random orthogonal matrix.
 *    qmult(a) returns q*a where q is a random real orthogonal matrix.
 *    qmult<T>(n) is the same as qmult(eye(n, as_<T>())).
 *
 *    called by randcolu, randcorr, randjorth, randsvd.
 *
 *    Reference:
 *    G. W. Stewart, The efficient generation of random
 *    orthogonal matrices with an application to condition estimators,
 *    SIAM J. Numer. Anal., 17 (1980), 403-409.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/qmult.hpp>
 * \endcode
 *
 **/
//==============================================================================
// qmult actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag qmult_ of functor qmult
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct qmult_ : ext::unspecified_<qmult_>
    {
      typedef ext::unspecified_<qmult_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::qmult_, qmult, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::qmult_, qmult, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::qmult_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = sizee[1] = nt2::numel(boost::proto::child_c<0>(e));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct  value_type < tag::qmult_, Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

} }

#endif

