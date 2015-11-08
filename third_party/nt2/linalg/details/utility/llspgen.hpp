//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_UTILITY_LLSPGEN_HPP_INCLUDED
#define NT2_LINALG_DETAILS_UTILITY_LLSPGEN_HPP_INCLUDED

#include <nt2/linalg/functions/llspgen.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::llspgen_, tag::cpu_,
                              (A0),
                              (scalar_<arithmetic_<A0> >)
                              (scalar_<arithmetic_<A0> >)
                              (scalar_<arithmetic_<A0> >)
                              (scalar_<arithmetic_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(4, (A0 a0, A0 a1, A0 a2, A0 a3),
                           (boost::proto::
                            make_expr<nt2::tag::llspgen_, container::domain>
                            (a0, a1, a2, a3)
                           )
                          )
      };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::llspgen_, tag::cpu_,
                              (A0)(T),
                              (scalar_<arithmetic_<A0> >)
                              (scalar_<arithmetic_<A0> >)
                              (scalar_<arithmetic_<A0> >)
                              (scalar_<arithmetic_<A0> >)
                              (target_<scalar_<arithmetic_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 5
                          , (A0 a0, A0 a1, A0 a2, A0 a3, T const& t),
                           (boost::proto::
                            make_expr<nt2::tag::llspgen_, container::domain>
                            (a0, a1, a2, a3,t)
                           )
                          )
      };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::llspgen_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0,nt2::tag::llspgen_,N0,nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
{
  typedef void                                                          result_type;
  typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
  typedef typename A0::value_type                                       type_t;


  result_type operator()( A0 & a0, A1 & a1 ) const
  {
    nt2::meta::as_<type_t> tgt;
    std::size_t m  = boost::proto::child_c<0>(a0);
    std::size_t n  = boost::proto::child_c<1>(a0);
    std::size_t q  = boost::proto::child_c<2>(a0);
    type_t nr = boost::proto::child_c<3>(a0);

    nt2::container::table<type_t> c = nt2::rand(m-n,1,tgt);
    nt2::container::table<type_t> y = nt2::rand(m,1,tgt);
    nt2::container::table<type_t> z = nt2::rand(n,1,tgt);

    type_t norm = (type_t)1./(nt2::globalnorm2(c)*nr);
    c = c*norm ; norm = type_t(1)/nt2::globalnorm2(y);
    y = y*norm ; norm = type_t(1)/nt2::globalnorm2(z);
    z = z*norm ;

    nt2::container::table<type_t> Y = nt2::eye(m,tgt) - type_t(2)*nt2::mtimes(y,nt2::trans(y));
    nt2::container::table<type_t> Z = nt2::eye(n,tgt) - type_t(2)*nt2::mtimes(z,nt2::trans(z));

    nt2::container::table<type_t> D(nt2::of_size(n,1));

    boost::proto::child_c<1>(a1) = nt2::zeros(n,1,tgt);

    for(size_t i=1; i <=n;++i)
    {
      D(i) =  nt2::pow((type_t)i/n,(type_t)q);
      boost::proto::child_c<1>(a1)(i) = (type_t) i*i;
    }
    y = nt2::flipud(D);
    D = nt2::from_diag(y);

    nt2::container::table<type_t> SS = nt2::vertcat(D,nt2::zeros(m-n,n,tgt));

    boost::proto::child_c<0>(a1) = nt2::mtimes(Y, nt2::mtimes(SS,nt2::trans(Z)));

    boost::proto::child_c<2>(a1) = nt2::mtimes(Y,nt2::vertcat(nt2::zeros(n,1,tgt),c) );

    nt2::container::table<type_t> b1 = nt2::mtimes(D,Z);
    b1 = nt2::mtimes(b1,boost::proto::child_c<1>(a1));
    boost::proto::child_c<3>(a1) = nt2::mtimes(Y,nt2::vertcat(b1,c));

  }
};

}
}

#endif
