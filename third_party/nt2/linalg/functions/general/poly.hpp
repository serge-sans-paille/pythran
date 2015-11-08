//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_POLY_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_POLY_HPP_INCLUDED

#include <nt2/linalg/functions/poly.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/nseig.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::poly_, N,nt2::container::domain> ))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type        In0;
    typedef typename A1::value_type                                value_type;
    typedef A0&                                                   result_type;
    typedef typename meta::is_complex<value_type>::type            is_cmplx_t;
    typedef typename meta::as_complex<value_type>::type               ctype_t;
    result_type operator()(A0& out, const A1& in) const
    {
      In0 & a = boost::proto::child_c<0>(in);
      BOOST_ASSERT_MSG(isvector(a)/* || issquare(a)*/, "input must be a vector or a square matrix");
      out.resize(in.extent());

      if (issquare(a))
        compute(out,  nseig(a), is_cmplx_t());
      else
        compute(out, a, is_cmplx_t());
      return out;
    }
  private:
  private:
    template <class S, class T> BOOST_FORCEINLINE
    void compute(S out, const T& e, boost::mpl::true_ const &) const
    {
       size_t n = length(e);
       table<value_type> tmp1;
       out = nt2::cath(One<ctype_t>(), nt2::zeros(1,n,nt2::meta::as_<value_type>()));

       for(size_t j=1; j <= n; ++j)
       {
         tmp1 = out(_(2u, j+1))- e(j)*out(_(1u, j)); //aliasing !
         out(_(2u, j+1)) = tmp1;
       }
    }

    template <class S, class T> BOOST_FORCEINLINE
    void compute(S out, const T& e, boost::mpl::false_ const &) const
    {
       size_t n = length(e);
       table<ctype_t> tmp,  tmp1;
       tmp = nt2::cath(One<ctype_t>(), nt2::zeros(1,n,nt2::meta::as_<ctype_t>()));

       for(size_t j=1; j <= n; ++j)
       {
         tmp1 = tmp(_(2u, j+1))- e(j)*tmp(_(1u, j)); //aliasing !
         tmp(_(2u, j+1)) = tmp1;
       }
       out = real(tmp);
    }
  };
} }

#endif
