//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BLKDIAG_HPP_INCLUDED

#include <nt2/core/functions/blkdiag.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/ismatrix.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// Generates blkdiag from 1 expression
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::blkdiag_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be  matrices
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using blkdiag: First input must be 2D."
                      );

      return a0;
    }
  };

  /// INTERNAL ONLY
  /// Generates blkdiag from 2 expressions
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::blkdiag_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::blkdiag_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 const& a1) const
    {
      // Expressions must be  matrices
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using blkdiag: First input must be 2D."
                      );

      BOOST_ASSERT_MSG( nt2::ismatrix(a1)
                      , "Error using blkdiag: Second input must be 2D."
                      );

      return boost::proto::make_expr< nt2::tag::blkdiag_
                                    , container::domain
                                    > (boost::cref(a0),boost::cref(a1));
    }
  };
} }

#endif
