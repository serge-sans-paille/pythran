//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_FREQSPACE_HPP_INCLUDED

#include <nt2/core/functions/freqspace.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/meshgrid.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_ < A0, nt2::tag::freqspace_
                                        , N0, nt2::container::domain
                                        >
                                ))
                                ((node_ < A1, nt2::tag::tie_
                                        , N1, nt2::container::domain
                                        >
                                ))
                            )
  {
    typedef void    result_type;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      typedef typename boost::proto::result_of::child_c<A0&,2>::value_type c0_t;
      typedef typename boost::dispatch::meta::semantic_of<c0_t>::type      s0_t;

      eval(a0,a1,N0(),N1(), typename meta::is_scalar<s0_t>::type() );
    }

    // [f] = freqspace(scalar)
    BOOST_FORCEINLINE result_type
    eval( A0& a0, A1& a1
        , boost::mpl::long_<3> const&, boost::mpl::long_<1> const&
        , boost::mpl::true_ const&
        ) const
    {
      typedef typename boost::proto::result_of
                            ::child_c<A1&,0>::value_type::value_type t_t;

      t_t s = t_t(2)/boost::proto::value(boost::proto::child_c<2>(a0));

      boost::proto::child_c<0>(a1) = _( t_t(0.), s, t_t(1.) );
    }

    // [f1,f2] = freqspace(scalar)
    BOOST_FORCEINLINE result_type
    eval( A0& a0, A1& a1
        , boost::mpl::long_<3> const&, boost::mpl::long_<2> const&
        , boost::mpl::true_ const&
        ) const
    {
      typedef typename boost::proto::result_of
                      ::child_c<A1&,0>::value_type::value_type t_t;

      std::ptrdiff_t n = boost::proto::value(boost::proto::child_c<2>(a0));
      t_t l,s,u;

      setup(n,l,s,u);

      a1 = nt2::tie( _(l,s,u), _(l,s,u) );
    }

    // [f] = freqspace(n, 'option')
    BOOST_FORCEINLINE result_type
    eval( A0& a0, A1& a1
        , boost::mpl::long_<4> const&, boost::mpl::long_<1> const&
        , boost::mpl::true_ const&
        ) const
    {
      typedef typename boost::proto::result_of
                            ::child_c<A1&,0>::value_type::value_type t_t;

      t_t n = t_t(boost::proto::value(boost::proto::child_c<2>(a0)));

      boost::proto::child_c<0>(a1) = _(t_t(0),2/n,2*(n-1)/n);
    }

    // [f1] = freqspace(size)
    BOOST_FORCEINLINE result_type
    eval( A0& a0, A1& a1
        , boost::mpl::long_<3> const&, boost::mpl::long_<1> const&
        , boost::mpl::false_ const&
        ) const
    {
      typedef typename boost::proto::result_of
                            ::child_c<A1&,0>::value_type::value_type t0_t;

      std::ptrdiff_t m = boost::proto::child_c<2>(a0)(begin_+1);

      t0_t l0, u0, s0;
      setup(m,l0,s0,u0);

      boost::proto::child_c<0>(a1) = _(l0,s0,u0);
    }

    // [f1,f2] = freqspace(size)
    BOOST_FORCEINLINE result_type
    eval( A0& a0, A1& a1
        , boost::mpl::long_<3> const&, boost::mpl::long_<2> const&
        , boost::mpl::false_ const&
        ) const
    {
      typedef typename boost::proto::result_of
                            ::child_c<A1&,0>::value_type::value_type t0_t;

      typedef typename boost::proto::result_of
                            ::child_c<A1&,1>::value_type::value_type t1_t;

      std::ptrdiff_t m = boost::proto::child_c<2>(a0)(begin_);
      std::ptrdiff_t n = boost::proto::child_c<2>(a0)(begin_+1);

      t0_t l0, u0, s0;
      t1_t l1, u1, s1;

      setup(m,l1,s1,u1);
      setup(n,l0,s0,u0);

      // These can't be merged as both can have different numels
      boost::proto::child_c<0>(a1) = _(l0,s0,u0);
      boost::proto::child_c<1>(a1) = _(l1,s1,u1);
    }

    // [f,g] = freqspace(size, 'option')
    BOOST_FORCEINLINE result_type
    eval( A0& a0, A1& a1
        , boost::mpl::long_<4> const&, boost::mpl::long_<2> const&
        , boost::mpl::false_ const&
        ) const
    {
      typedef typename boost::proto::result_of
                            ::child_c<A1&,0>::value_type::value_type t0_t;

      typedef typename boost::proto::result_of
                            ::child_c<A1&,1>::value_type::value_type t1_t;

      std::ptrdiff_t m = boost::proto::child_c<2>(a0)(begin_);
      std::ptrdiff_t n = boost::proto::child_c<2>(a0)(begin_+1);

      t0_t l0, u0, s0;
      t1_t l1, u1, s1;

      setup(m,l1,s1,u1);
      setup(n,l0,s0,u0);

      a1 = meshgrid( _(l0,s0,u0), _(l1,s1,u1) );
    }

    private:

    template<typename T>
    static BOOST_FORCEINLINE void setup(std::ptrdiff_t n, T& l, T& s, T& u)
    {
      T d = is_odd(n) ? T(1) : T(0);

      l =  d/n - T(1);
      s =  T(2)/n;
      u =  T(1) + (d-2)/n;
    }
  };
} }

#endif
