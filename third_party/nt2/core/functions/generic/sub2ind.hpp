#if !BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GENERIC_SUB2IND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GENERIC_SUB2IND_HPP_INCLUDED

#include <nt2/core/functions/sub2ind.hpp>
#include <nt2/sdk/parameters.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/touint.hpp>
#include <nt2/include/functions/as_size.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace nt2 { namespace ext
{
   #define BOOST_PP_FILENAME_1 "nt2/core/functions/generic/sub2ind.hpp"
   #define BOOST_PP_ITERATION_LIMITS (2, BOOST_PP_INC(NT2_MAX_DIMENSIONS))
   #include BOOST_PP_ITERATE()
} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  #define M0(z,n,t) (t<arithmetic_<A1> >)
  #define M1(z,n,t) nt2::touint(a##n - one)

  /// INTERNAL ONLY - sub2ind(ettent,D1,D2)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sub2ind_, tag::cpu_
                            , (SZ)(A1)
                            , (fusion_sequence_<SZ>)
                              BOOST_PP_REPEAT(N,M0,generic_)
                            )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE
    result_type operator()(SZ const& sz, BOOST_PP_ENUM_PARAMS(N,A1 const& a) ) const
    {
      A1 one  = One<A1>();
      A1 that = one
              + splat<A1> ( as_index ( sz, boost::fusion::make_vector
                                        ( BOOST_PP_ENUM(N, M1, ~) )
                                    )
                          );
      return that;
    }
  };

  /// INTERNAL ONLY - ind2sub(size,IND)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sub2ind_, tag::cpu_
                            , (SZ)(A1)
                            , ((ast_<SZ,nt2::container::domain>))
                              BOOST_PP_REPEAT(N,M0,scalar_)
                            )
  {
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(N)
                          , (SZ const& sz, BOOST_PP_ENUM_PARAMS(N,A1 a) )
                          , ( nt2::sub2ind( nt2::as_size(sz)
                                          , BOOST_PP_ENUM_PARAMS(N,a)
                                          )
                            )
                          )
  };

  #undef M1
  #undef M0
  #undef N

#endif
