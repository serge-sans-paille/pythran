//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_MESHGRID_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_MESHGRID_HPP_INCLUDED

#include <nt2/core/functions/meshgrid.hpp>
#include <nt2/core/functions/details/grids.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <nt2/include/functions/tie.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::meshgrid_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_ < A0, nt2::tag::meshgrid_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , N1, nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Don't feed more than you ask
      BOOST_ASSERT_MSG( N0::value >= N1::value
                      , "meshgrid: Too many output arguments"
                      );

      typedef details::fill_grids < A0,A1,tag::meshgrid_
                                  , N0::value, N1::value
                                  > filler_t;
      boost::simd::meta::iterate<N0::value>( filler_t(a0,a1) );
    }
  };
} }

#endif
