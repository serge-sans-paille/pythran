//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_CONTAINER_MAX_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_CONTAINER_MAX_HPP_INCLUDED

#include <nt2/arithmetic/functions/max.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2
{
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::max_, max, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::max_, max, 3)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::max_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call< nt2::tag::maximum_(A0 const&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      return nt2::maximum(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::max_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename meta::call< nt2::tag::maximum_(A0 const&, A2 const&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      BOOST_ASSERT_MSG
      ( nt2::numel(a1) == 0
      , "??? Error using ==> max\n"
        "MAX with two matrices to compare and a working dimension is not supported."
      );

      return nt2::maximum(a0,a2);
    }
  };
} }

#endif
