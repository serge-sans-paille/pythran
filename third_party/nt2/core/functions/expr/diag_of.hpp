//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DIAG_OF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DIAG_OF_HPP_INCLUDED

#include <nt2/core/functions/diag_of.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/ismatrix.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::diag_of_, tag::cpu_, (A0), ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::diag_of_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "??? Error using ==> diag_of "
                        "First input must be 2D"
                      );

      std::size_t offset  = 1 + nt2::size(a0,1);

      return boost::proto::make_expr< nt2::tag::diag_of_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , offset
                                      );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::offset_diag_of_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::offset_diag_of_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , std::size_t
                                          , A1
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "??? Error using ==> diag_of "
                        "First input must be 2D"
                      );

      std::size_t offset  = 1 + nt2::size(a0,1);
      std::size_t start   = (a1 > 0) ? a1*nt2::size(a0,1) : -a1;

      return boost::proto::make_expr< nt2::tag::offset_diag_of_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , start
                                      , offset
                                      , a1
                                      );
    }
  };
} }

#endif
