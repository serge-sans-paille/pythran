//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_RESIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_RESIZE_HPP_INCLUDED

#include <nt2/core/functions/resize.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_ < A0, nt2::tag::resize_
                                      , N , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                base_type;
    typedef typename meta::strip<base_type>::type              result_type;
    typedef typename meta::as_index<result_type>::type         i_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      i_t nl = splat<i_t>(boost::proto::value(boost::proto::child_c<2>(a0)));
      i_t pos = nt2::enumerate<i_t>( p );

      // Return 0 if out of bounds value in a0 instead
      return nt2::if_else
            ( nt2::le ( pos, nl )
            , nt2::run( boost::proto::child_c<0>(a0), nt2::min(pos,nl), t )
            , Zero<result_type>()
            );
    }
  };
} }

#endif
