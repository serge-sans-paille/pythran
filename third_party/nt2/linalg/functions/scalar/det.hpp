//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_DET_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_DET_HPP_INCLUDED

#include <nt2/linalg/functions/det.hpp>
#include <nt2/include/functions/getrf.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/globalprod.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type                 type_t;
    typedef typename boost::dispatch::meta::as_floating<type_t>
                                          ::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG( issquare(a0)
                      , "DET: Argument must be a square matrix"
                      );

      nt2::container::table<typename A0::value_type>  lu(a0);
      nt2::container::table<nt2_la_int>               ip;

      // Factorize A as L/U
      nt2_la_int  info = nt2::getrf(boost::proto::value(lu),boost::proto::value(ip));
      boost::dispatch::ignore_unused(info);

      // DET(A) is the product of LU(A) diagonal by -1 at the power of
      // the number of non-permutations done in LU(A)
      std::size_t n     = nt2::numel(ip);
      result_type sign  = One<result_type>();

      // TODO: Parallelize this somehow ?
      for(std::size_t i = 1;i <= n;++i)
        sign  *= (ip(i) != nt2_la_int(i)) ? 1 : -1;

      return nt2::globalprod(nt2::diag_of(lu))*sign;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>
                                          ::type  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
} }

#endif
