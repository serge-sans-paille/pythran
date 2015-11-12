//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BAND_HPP_INCLUDED

#include <nt2/core/functions/band.hpp>
#include <nt2/core/functions/colon.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr,int N>
  struct  size_of<nt2::tag::band_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::band_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::band_
                                          , container::domain
                                          , A0 const&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using band: First input must be 2D."
                      );

      return boost::proto::make_expr< nt2::tag::band_
                                    , container::domain
                                    > ( boost::cref(a0) );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::band_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::band_
                                          , container::domain
                                          , A0 const&
                                          , A1
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using band: First input must be 2D."
                      );

      // Band width must be positive
      BOOST_ASSERT_MSG( a1 >= 0
                      , "Error using band: Invalid band shape requested."
                      );

      return boost::proto::make_expr< nt2::tag::band_
                                    , container::domain
                                    > ( boost::cref(a0), a1);
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::band_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< integer_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::band_
                                          , container::domain
                                          , A0 const&
                                          , A1
                                          , A2
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1, A2 a2) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using band: First input must be 2D."
                      );

      // Relative sub/superdiagonal index must be ordered
      BOOST_ASSERT_MSG( a1 <= a2
                      , "Error using band: Invalid band shape requested."
                      );

      return boost::proto::make_expr< nt2::tag::band_
                                    , container::domain
                                    > ( boost::cref(a0), a1, a2);
    }
  };
} }

#endif
