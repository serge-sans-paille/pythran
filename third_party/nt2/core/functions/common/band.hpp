//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BAND_HPP_INCLUDED

#include <nt2/core/functions/band.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/enumerate.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_ < A0, nt2::tag::band_
                                      , boost::mpl::long_<1>
                                      , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                       result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type        i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type   s_t;

      // Retrieve 2D position from the linear index
      s_t const pos = as_subscript(_2D(a0.extent()),enumerate<i_t>(p));

      // Return the upper triangular section with 1 on the diagonal
      return nt2::if_else_zero( nt2::eq(pos[0],pos[1])
                              , nt2::run(boost::proto::child_c<0>(a0),p,t)
                              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_ < A0, nt2::tag::band_
                                      , boost::mpl::long_<2>
                                      , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                       result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type                    i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type               s_t;
      typedef typename nt2::meta::as_signed<typename s_t::value_type>::type p_t;

      // Retrieve the band width
      std::ptrdiff_t o = boost::proto::value(boost::proto::child_c<1>(a0));

      // Retrieve 2D position from the linear index
      s_t  const pos = as_subscript(_2D(a0.extent()), nt2::enumerate<i_t>(p) );
      p_t const is  = bitwise_cast<p_t>(pos[0]);
      p_t const js  = bitwise_cast<p_t>(pos[1]);

      // Return the band between +/-offset around the main diagonal
      return nt2::if_else_zero( nt2::logical_and( nt2::le(is,js + o)
                                                , nt2::ge(is,js - o)
                                                )
                              , nt2::run(boost::proto::child_c<0>(a0),p,t)
                              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_ < A0, nt2::tag::band_
                                      , boost::mpl::long_<3>
                                      , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                       result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type                    i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type               s_t;
      typedef typename nt2::meta::as_signed<typename s_t::value_type>::type p_t;

      // Retrieve the band width and positive them
      std::ptrdiff_t const od = boost::proto::value(boost::proto::child_c<1>(a0));
      std::ptrdiff_t const ou = boost::proto::value(boost::proto::child_c<2>(a0));

      // Retrieve 2D position from the linear index
      s_t const pos = as_subscript(_2D(a0.extent()), nt2::enumerate<i_t>(p) );
      p_t const is  = bitwise_cast<p_t>(pos[0]);
      p_t const js  = bitwise_cast<p_t>(pos[1]);

      // Return the band between +/-offset around the main diagonal
      return nt2::if_else_zero( nt2::logical_and( nt2::le(is,js - od)
                                                , nt2::ge(is,js - ou)
                                                )
                              , nt2::run(boost::proto::child_c<0>(a0),p,t)
                              );
    }
  };
} }

#endif
