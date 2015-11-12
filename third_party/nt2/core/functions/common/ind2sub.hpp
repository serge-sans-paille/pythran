//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_IND2SUB_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_IND2SUB_HPP_INCLUDED

#include <nt2/core/functions/ind2sub.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/mod.hpp>
#include <boost/assert.hpp>

#if !defined(BOOST_DISABLE_ASSERTS)
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/numel.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_ < A0, nt2::tag::ind2sub_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , N1, nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void                                      result_type;
    typedef typename A0::value_type                   value_type;
    typedef typename nt2::make_size<N1::value>::type  dims_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Get base index
      value_type bi = boost::proto::value(boost::proto::child_c<2>(a0));

      // Compute real size to use
      dims_t dz(boost::proto::value(boost::proto::child_c<0>(a0)));

      // Check every indices is inside requested size
      BOOST_ASSERT_MSG( nt2::globalall(   boost::proto::child_c<1>(a0)
                                      <=  value_type(nt2::numel(dz)+bi-1)
                                      )
                      , "ind2sub: Out of range index"
                      );

      // Fill with proper computation
      eval( boost::proto::child_c<1>(a0), a1, dz, bi
          , boost::mpl::int_<0>()
          , boost::mpl::int_<dims_t::static_size>()
          , boost::mpl::bool_<dims_t::static_size==2>()
          );
    }

    // General case
    template<typename X, typename N, typename M,typename Size>
    BOOST_DISPATCH_FORCE_INLINE void
    eval( X const& a0, A1& a1, Size const& sz, value_type bi
        , N const&, M const& m, boost::mpl::false_ const&
        ) const
    {
      value_type ls = sz[N::value] ? sz[N::value] : 1;

      boost::proto::child_c<N::value>(a1) = nt2::mod(a0-bi,ls)+bi;

      eval( ((a0-boost::proto::child_c<N::value>(a1))/ls) + bi
          , a1, sz, bi
          , boost::mpl::int_<N::value+1>()
          , m
          , boost::mpl::bool_<(N::value+1 == M::value-2)>()
          );
    }

    // 2D ind2sub - remquo + additionnal base index work
    template<typename X,typename N, typename M,typename Size>
    BOOST_DISPATCH_FORCE_INLINE void
    eval( X const& a0, A1& a1, Size const& sz, value_type bi
        , N const&, M const&, boost::mpl::true_ const&
        ) const

    {
      value_type ls = sz[N::value] ? sz[N::value] : 1;

      // Perform real-enabled modulo here after base index realignment
      boost::proto::child_c<N::value>(a1) = nt2::mod(a0-bi,ls)+bi;

      // The j = p-i/ls comes from matlab ind2sub. It helps not
      // requiring costly calls to trunc when calling ind2sub on
      // real values.
      boost::proto::
      child_c<N::value+1>(a1) = ( (a0-boost::proto::child_c<N::value>(a1))/ls )
                              + bi;
    }

    // 1D ind2sub - just copy over
    template<typename X,typename Size>
    BOOST_DISPATCH_FORCE_INLINE void
    eval( X const& a0, A1& a1, Size const&, value_type
        , boost::mpl::int_<0> const &, boost::mpl::int_<1> const &
        , boost::mpl::false_ const&
        ) const
    {
      boost::proto::child_c<0>(a1) = a0;
    }
  };
} }

#endif
