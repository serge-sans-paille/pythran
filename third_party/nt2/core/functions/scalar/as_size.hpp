//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_AS_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_AS_SIZE_HPP_INCLUDED

#include <nt2/core/functions/as_size.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::as_size_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_< A0 >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::as_size_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0)
                          , (nt2::of_size(a0, a0))
                          )
  };

  #define M0(z,n,t) (A##n)
  #define M1(z,n,t) (scalar_< arithmetic_<A##n> >)

  #define M2(z,n,t)                                                   \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::as_size_, tag::cpu_           \
                            , BOOST_PP_REPEAT(n,M0,~)                 \
                            , BOOST_PP_REPEAT(n,M1,~)                 \
                            )                                         \
  {                                                                   \
    BOOST_DISPATCH_RETURNS( n                                         \
                          , (BOOST_PP_ENUM_BINARY_PARAMS(n,A,a))      \
                          , (nt2::of_size(BOOST_PP_ENUM_PARAMS(n,a))) \
                          )                                           \
  };                                                                  \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M2,~)

  #undef M2
  #undef M1
  #undef M0
} }

#endif
