  //==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_SCALAR_ISINSIDE_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_SCALAR_ISINSIDE_HPP_INCLUDED

#include <nt2/predicates/functions/isinside.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isinside_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::fusion::result_of::at_c<A0,0>::type   at_t;
    typedef typename meta::strip<at_t>::type                      base_t;
    typedef typename boost::simd::meta::as_logical<base_t>::type  result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0,const A1& a1) const
    {
      typedef typename boost::fusion::result_of::size<A0>::type sz_t;
      return eval(a0,a1,boost::mpl::int_<sz_t::value-1>());
    }

    template<class N> BOOST_FORCEINLINE result_type
    eval(const A0& a0,const A1& a1, N const&) const
    {
      return l_and( eval(a0,a1, boost::mpl::int_<N::value-1>())
                  , lt( boost::fusion::at_c<N::value>(a0)
                      , splat<base_t>(boost::fusion::at_c<N::value>(a1))
                      )
                  );
    }

    BOOST_FORCEINLINE result_type
    eval(const A0& a0,const A1& a1,boost::mpl::int_<0> const&) const
    {
      return lt ( boost::fusion::at_c<0>(a0)
                , splat<base_t>(boost::fusion::at_c<0>(a1))
                );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isinside_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<A1>)
                              (fusion_sequence_<A2>)
                            )
  {
    typedef typename boost::fusion::result_of::at_c<A0,0>::type   at_t;
    typedef typename meta::strip<at_t>::type                      base_t;
    typedef typename boost::simd::meta::as_logical<base_t>::type  result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0,const A1& a1,const A2& a2) const
    {
      typedef typename boost::fusion::result_of::size<A0>::type sz_t;
      return eval(a0,a1,a2,boost::mpl::int_<sz_t::value-1>());
    }

    template<class N> BOOST_FORCEINLINE result_type
    eval(const A0& a0,const A1& a1,const A2& a2, N const&) const
    {
      return l_and( eval(a0,a1,a2, boost::mpl::int_<N::value-1>())
                  , eval_at ( boost::fusion::at_c<N::value>(a0)
                            , boost::fusion::at_c<N::value>(a1)
                            , boost::fusion::at_c<N::value>(a2)
                            )
                  );
    }

    BOOST_FORCEINLINE result_type
    eval(const A0& a0,const A1& a1,const A2& a2, boost::mpl::int_<0> const&) const
    {
      return eval_at( boost::fusion::at_c<0>(a0)
                    , boost::fusion::at_c<0>(a1)
                    , boost::fusion::at_c<0>(a2)
                    );
    }

    template<class T0,class T1, class T2> BOOST_FORCEINLINE
    result_type eval_at(const T0& a0,const T1& a1,const T2& a2) const
    {
      return l_and( ge( a0, splat<base_t>(a2))
                  , lt( a0, splat<base_t>(a2+a1))
                  );
    }
  };
} }

#endif
