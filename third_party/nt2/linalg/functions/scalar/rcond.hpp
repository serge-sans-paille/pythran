//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_RCOND_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_RCOND_HPP_INCLUDED

#include <nt2/linalg/functions/rcond.hpp>
#include <nt2/include/functions/getrf.hpp>
#include <nt2/include/functions/getri.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/mnorm.hpp>
#include <nt2/include/functions/mnorm1.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rcond_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(issquare(a0), "rcond for non square matrix");
      nt2::container::table<type_t>  lu(a0);
      nt2::container::table<nt2_la_int>               ip;

      nt2::getrf(boost::proto::value(lu), boost::proto::value(ip) );
      nt2::getri(boost::proto::value(lu), boost::proto::value(ip) );
      return nt2::rec(nt2::mnorm1(a0) * nt2::mnorm1(lu));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rcond_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return a0 ? One<A0>() : Zero<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rcond_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type      rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( issquare(a0)
                      , "rcondition number of non square matrix"
                      );
      {
        nt2::container::table<type_t>  lu(a0);
        nt2::container::table<nt2_la_int>               ip;

      nt2::getrf(boost::proto::value(lu), boost::proto::value(ip) );
      nt2::getri(boost::proto::value(lu), boost::proto::value(ip) );
        return nt2::rec(nt2::mnorm(a0, a1)*nt2::mnorm(lu, a1));
      }
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rcond_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> > )
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>::type result_type;
    result_type operator()(A0 const & a0,  A1 const&)
    {
      return a0 ? One<A0>() : Zero<A0>();
    }
  };
} }

#endif
